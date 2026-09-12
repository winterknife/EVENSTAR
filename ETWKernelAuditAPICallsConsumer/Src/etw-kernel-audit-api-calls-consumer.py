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
[!] Usage: uv.exe run --script etw-kernel-audit-api-calls-consumer.py [PID of process to be monitored] [output filename]
[!] Note: Please launch from an admin shell to be able to consume events.
"""

import sys
import etw
from etw.etw import ProviderParameters
import json
import os
import lief
import windows
from urllib.request import urlopen
from pathlib import Path
from uuid import UUID
from bisect import bisect_right
from datetime import datetime, timezone, timedelta

events = []
filter_pid = 0


def event_callback(event_tufo):
    event_id = event_tufo[0]
    payload = event_tufo[1]

    calling_pid = payload["EventHeader"]["ProcessId"]
    calling_tid = payload["EventHeader"]["ThreadId"]

    user_stack = []
    kernel_stack = []
    for retaddr in payload["EventExtendedData"]["StackTrace64"]["Address"]:
        if retaddr > 0x7FFFFFFEFFFF:  # MM_HIGHEST_USER_ADDRESS
            kernel_stack.append(f"0x{retaddr:x}")
            continue
        user_stack.append(f"0x{retaddr:x}")

    timestamp = (
        (
            datetime(1601, 1, 1, tzinfo=timezone.utc)
            + timedelta(microseconds=payload["EventHeader"]["TimeStamp"] // 10)
        )
        .isoformat(timespec="microseconds")
        .replace("+00:00", "Z")
    )

    if event_id == 2:
        event_dict = {
            "Description": "Cross-process attempt at process termination",
            "Timestamp": timestamp,
            "Calling PID": calling_pid,
            "Calling TID": calling_tid,
            "Target PID": payload["TargetProcessId"],
            "NTSTATUS": hex(payload["ReturnCode"]),
            "User Stack": user_stack,
            "Kernel Stack": kernel_stack,
        }
        events.append(event_dict)
    elif event_id == 3:
        event_dict = {
            "Description": "Attempt at Object Manager symbolic link object creation",
            "Timestamp": timestamp,
            "Calling PID": calling_pid,
            "Calling TID": calling_tid,
            "Symlink Name": payload["LinkSourceName"],
            "Target Name": payload["LinkTargetName"],
            "Desired Access": hex(payload["DesiredAccess"]),
            "NTSTATUS": hex(payload["ReturnCode"]),
            "User Stack": user_stack,
            "Kernel Stack": kernel_stack,
        }
        events.append(event_dict)
    elif event_id == 4:
        event_dict = {
            "Description": "Attempt at thread CONTEXT modification via nt!NtSetContextThread",
            "Timestamp": timestamp,
            "Calling PID": calling_pid,
            "Calling TID": calling_tid,
            "NTSTATUS": hex(payload["ReturnCode"]),
            "User Stack": user_stack,
            "Kernel Stack": kernel_stack,
        }
        events.append(event_dict)
    elif event_id == 5:
        event_dict = {
            "Description": "Attempt at opening a handle to a process object",
            "Timestamp": timestamp,
            "Calling PID": calling_pid,
            "Calling TID": calling_tid,
            "Target PID": payload["TargetProcessId"],
            "Desired Access": hex(payload["DesiredAccess"]),
            "NTSTATUS": hex(payload["ReturnCode"]),
            "User Stack": user_stack,
            "Kernel Stack": kernel_stack,
        }
        events.append(event_dict)
    elif event_id == 6:
        event_dict = {
            "Description": "Attempt at opening a handle to a thread object",
            "Timestamp": timestamp,
            "Calling PID": calling_pid,
            "Calling TID": calling_tid,
            "Target PID": payload["TargetProcessId"],
            "Target TID": payload["TargetThreatId"],
            "Desired Access": hex(payload["DesiredAccess"]),
            "NTSTATUS": hex(payload["ReturnCode"]),
            "User Stack": user_stack,
            "Kernel Stack": kernel_stack,
        }
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

    params = ProviderParameters(
        event_property=4, event_filters=[]
    )  # EVENT_ENABLE_PROPERTY_STACK_TRACE

    providers = [
        etw.ProviderInfo(
            "Microsoft-Windows-Kernel-Audit-API-Calls",
            etw.GUID("{e02a841c-75a3-4fa7-afc8-ae09cf9b7f23}"),
            level=etw.evntrace.TRACE_LEVEL_INFORMATION,
            any_keywords=None,
            all_keywords=None,
            params=params.get(),
        )
    ]

    job = etw.ETW(
        session_name="etw-kernelauditapicalls",
        providers=providers,
        event_callback=event_callback,
        ignore_exists_error=False,
        pid_whitelist=[filter_pid],
    )

    print("[+] Starting capture.")
    job.start()

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
