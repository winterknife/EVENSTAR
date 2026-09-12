#!/usr/bin/env -S uv run --script
#
# /// script
# requires-python = "==3.9.*"
# dependencies = ["pywintrace", "lief-extended", "pythonforwindows"]
# [tool.uv.sources]
# pywintrace = { url = "https://github.com/fireeye/pywintrace/releases/download/v0.3.0/pywintrace-0.3.0-py3-none-any.whl" }
# lief-extended = { path = "./lief_extended-2.0.0.post3335-cp39-cp39-win_amd64.whl" }
# pythonforwindows = { url = "https://files.pythonhosted.org/packages/01/3b/bf4a9a401ea2cd867aa4522a97ffa2f5b60a38c3249887f77f0f997d7743/pythonforwindows-1.0.4-py3-none-any.whl" }
# ///


"""
[!] Usage: uv.exe run --script etw-syscall-consumer.py [PID of process to be monitored] [output filename]
[!] Note: Please launch from an admin shell to be able to consume events.
"""

import sys
import etw
from etw.common import RETURN_RAW_UNFORMATTED_DATA
import ctypes
import json
from datetime import datetime, timedelta, timezone
import os
from pathlib import Path
from uuid import UUID
from urllib.request import urlopen
from bisect import bisect_right
import lief
import windows

pending = {}
events = []
filter_pid = 0
event_guids = {
    51: bytes(etw.GUID("{ce1dbfb4-137e-4da6-87b0-3f59aa102cbc}")),
    32: bytes(etw.GUID("{def2fe46-7bd6-4b80-bd94-f57fe20d0ce3}")),
}


def event_callback(event_tufo):
    payload = event_tufo[1].contents
    event_id = payload.EventHeader.EventDescriptor.Opcode
    if event_id not in (51, 32):
        return
    if bytes(payload.EventHeader.ProviderId) != event_guids[event_id]:
        return
    data = ctypes.string_at(payload.UserData, payload.UserDataLength)
    cpu = payload.BufferContext.ProcessorNumber

    if event_id == 51:
        if len(data) != 8:
            return
        syscall_kva = hex(int.from_bytes(data[:8], "little"))
        timestamp = payload.EventHeader.TimeStamp
        event_dict = {"Timestamp": timestamp, "Syscall KVA": syscall_kva}
        pending.setdefault((timestamp, cpu), []).append(event_dict)
    elif event_id == 32:
        if len(data) < 16 or (len(data) - 16) % 8:
            return
        timestamp = int.from_bytes(data[:8], "little")
        matches = pending.get((timestamp, cpu), [])
        if len(matches) != 1:
            return
        syscall = pending.pop((timestamp, cpu))[0]
        pid = int.from_bytes(data[8:12], "little")
        if filter_pid != pid:
            return
        tid = int.from_bytes(data[12:16], "little")
        user_stack = []
        kernel_stack = []
        for i in range(16, len(data), 8):
            retaddr = int.from_bytes(data[i : i + 8], "little")
            if retaddr > 0x7FFFFFFEFFFF:  # MM_HIGHEST_USER_ADDRESS
                kernel_stack.append(f"0x{retaddr:x}")
                continue
            user_stack.append(f"0x{retaddr:x}")
        if not user_stack:
            return
        event_dict = {
            "Timestamp": timestamp,
            "PID": pid,
            "TID": tid,
            "User Stack": user_stack,
            "Kernel Stack": kernel_stack,
        }
        event_dict["Syscall KVA"] = syscall["Syscall KVA"]
        events.append(event_dict)


def main():
    if len(sys.argv) != 3:
        print("[-] Invalid args.")
        print(__doc__)
        sys.exit(0)

    globals()["filter_pid"] = int(sys.argv[1])
    filename = sys.argv[2]

    symbols = {}
    image_sizes = {}
    for image_name, prefix in (("ntoskrnl.exe", "nt"), ("ntdll.dll", "ntdll")):
        binary = lief.PE.parse(
            str(Path(os.environ["SystemRoot"]) / "System32" / image_name)
        )
        image_sizes[prefix] = binary.optional_header.sizeof_image
        pdb_name = Path(binary.codeview_pdb.filename).name
        pdb_key = (
            UUID(binary.codeview_pdb.guid).hex.upper() + f"{binary.codeview_pdb.age:x}"
        )
        pdb_path = (
            Path(__file__).resolve().with_name(f"{Path(pdb_name).stem}-{pdb_key}.pdb")
        )
        if not pdb_path.is_file():
            url = f"https://msdl.microsoft.com/download/symbols/{pdb_name}/{pdb_key}/{pdb_name}"
            with urlopen(url, timeout=30) as response:
                pdb_path.write_bytes(response.read())
        debuginfo = lief.pdb.load(str(pdb_path))
        if (
            debuginfo is None
            or UUID(debuginfo.guid) != UUID(binary.codeview_pdb.guid)
            or debuginfo.age < binary.codeview_pdb.age
        ):
            print("[-] PDB not found.")
            sys.exit(0)
        symbols[prefix] = {}
        for symbol in debuginfo.public_symbols:
            if (
                symbol is not None
                and 0 < symbol.RVA < binary.optional_header.sizeof_image
            ):
                name = symbol.name
                if prefix == "ntdll" and name.startswith("Zw"):
                    name = "Nt" + name[2:]
                symbols[prefix].setdefault(symbol.RVA, f"{prefix}!{name}")

    ntdll_rvas = sorted(symbols["ntdll"])
    ntoskrnl_rvas = sorted(symbols["nt"])

    advapi32 = ctypes.WinDLL("advapi32", use_last_error=True)
    kernel32 = ctypes.WinDLL("kernel32", use_last_error=True)

    primary_token = windows.current_process.token
    previous_privileges = primary_token.privileges
    primary_token.enable_privilege("SeDebugPrivilege")
    ntoskrnl_base = None
    for module in windows.system.modules:
        if module.name.rsplit(b"\\", 1)[-1].lower() == b"ntoskrnl.exe":
            ntoskrnl_base = module.Base
            break
    if not ntoskrnl_base:
        print("[-] ntoskrnl.exe base not found.")
        sys.exit(0)
    primary_token.adjust_privileges(previous_privileges)
    print(
        f"[+] ntoskrnl.exe image base KVA: 0x{ntoskrnl_base & 0xFFFFFFFFFFFFFFFF:16X}"
    )

    target_process = windows.winobject.process.WinProcess(pid=filter_pid)
    ntdll_base = None
    for module in target_process.peb.modules:
        if module.name.lower() == "ntdll.dll":
            ntdll_base = module.baseaddr
            break
    if not ntdll_base:
        print("[-] ntdll.dll base not found.")
        sys.exit(0)
    print(f"[+] ntdll.dll image base UVA: 0x{ntdll_base:016X}")

    providers = [
        etw.ProviderInfo(
            "SystemSyscallProviderGuid",
            etw.GUID("{434286f7-6f1b-45bb-b37e-95f623046c7c}"),
            level=etw.evntrace.TRACE_LEVEL_INFORMATION,
            any_keywords=0x1,  # SYSTEM_SYSCALL_KW_GENERAL
            all_keywords=None,
        )
    ]

    job = etw.ETW(
        session_name="etw-syscall",
        providers=providers,
        event_callback=event_callback,
        ignore_exists_error=False,
        pid_whitelist=[],
        callback_data_flag=RETURN_RAW_UNFORMATTED_DATA,
    )

    job.properties.get().contents.LogFileMode |= (
        etw.evntrace.EVENT_TRACE_SYSTEM_LOGGER_MODE
    )

    job.properties.get().contents.Wnode.ClientContext = 1  # QPC

    job.trace_logfile = etw.evntrace.EVENT_TRACE_LOGFILE()
    job.trace_logfile.LoggerName = job.session_name
    job.trace_logfile.ProcessTraceMode = (
        etw.evntcons.PROCESS_TRACE_MODE_REAL_TIME
        | etw.evntcons.PROCESS_TRACE_MODE_EVENT_RECORD
        | etw.evntcons.PROCESS_TRACE_MODE_RAW_TIMESTAMP
    )

    TraceSetInformation = advapi32.TraceSetInformation
    TraceSetInformation.argtypes = [
        etw.evntrace.TRACEHANDLE,
        ctypes.c_int,
        ctypes.c_void_p,
        ctypes.c_ulong,
    ]
    TraceSetInformation.restype = ctypes.c_ulong

    stack_event = ctypes.create_string_buffer(
        bytes(etw.GUID("{ce1dbfb4-137e-4da6-87b0-3f59aa102cbc}"))  # EventGuid
        + bytes([51])  # Type
        + bytes(7),  # Reserved
        24,
    )

    qpc_frequency = ctypes.c_longlong()
    qpc_before = ctypes.c_longlong()
    qpc_after = ctypes.c_longlong()
    kernel32.QueryPerformanceFrequency(ctypes.byref(qpc_frequency))
    kernel32.QueryPerformanceCounter(ctypes.byref(qpc_before))
    utc_anchor = datetime.now(timezone.utc)
    kernel32.QueryPerformanceCounter(ctypes.byref(qpc_after))
    qpc_anchor = (qpc_before.value + qpc_after.value) // 2

    print("[+] Starting capture.")
    job.start()

    status = TraceSetInformation(
        job.provider.session_handle,
        3,  # TraceStackTracingInfo
        ctypes.byref(stack_event),
        ctypes.sizeof(stack_event),
    )
    if status != 0:
        job.stop()
        print(f"[-] TraceSetInformation error: 0x{status & 0xFFFFFFFF:08X}")
        sys.exit(0)

    try:
        input("[+] Press Enter to stop.")
    except KeyboardInterrupt:
        pass
    finally:
        stats = job.query()
        print("[+] Buffers written: ", stats.BuffersWritten)
        print("[+] Events lost: ", stats.EventsLost)
        print("[+] Real-time buffers lost: ", stats.RealTimeBuffersLost)
        print("[+] Stopping capture.")
        job.stop()

    for event in events:
        elapsed_us = (
            (event["Timestamp"] - qpc_anchor) * 1_000_000 // qpc_frequency.value
        )
        event["Timestamp"] = (utc_anchor + timedelta(microseconds=elapsed_us)).strftime(
            "%Y-%m-%dT%H:%M:%S.%fZ"
        )
        rva = int(event["Syscall KVA"], 16) - ntoskrnl_base
        syscall = symbols["nt"].get(rva)
        if syscall is not None:
            event["Syscall"] = syscall
            del event["Syscall KVA"]
        for index, retaddr in enumerate(event["User Stack"]):
            rva = int(retaddr, 16) - ntdll_base
            if not 0 <= rva < image_sizes["ntdll"]:
                continue
            offset = bisect_right(ntdll_rvas, rva) - 1
            if offset >= 0:
                symbol_rva = ntdll_rvas[offset]
                event["User Stack"][
                    index
                ] = f"{symbols['ntdll'][symbol_rva]}+0x{rva - symbol_rva:x}"
        for index, retaddr in enumerate(event["Kernel Stack"]):
            rva = int(retaddr, 16) - ntoskrnl_base
            if not 0 <= rva < image_sizes["nt"]:
                continue
            offset = bisect_right(ntoskrnl_rvas, rva) - 1
            if offset >= 0:
                symbol_rva = ntoskrnl_rvas[offset]
                event["Kernel Stack"][
                    index
                ] = f"{symbols['nt'][symbol_rva]}+0x{rva - symbol_rva:x}"

    try:
        file = open(filename, "w", encoding="utf-8")
    except OSError:
        print("[-] Invalid file path.")
        sys.exit(0)

    json.dump(events, file, indent=4, default=str, ensure_ascii=False)
    file.close()


if __name__ == "__main__":
    main()
