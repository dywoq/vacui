#!/usr/bin/env python3

# Copyright 2026 dywoq - Apache License 2.0
# A part of https://github.com/dywoq/vacui

import subprocess
import sys

def run_cmd(cmd, cwd=None, env=None, capture=True):
    if capture: 
        process = subprocess.Popen(
            cmd,
            shell=True,
            cwd=cwd,
            env=env,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
            bufsize=1 
        )
 
        for line in process.stdout:
            print(line, end='')
            sys.stdout.flush()

        process.wait()
        return process.returncode
    
    return subprocess.call(cmd, shell=True, cwd=cwd, env=env)

def main() -> None:
    print("Building kernel...")
    run_cmd("make all", cwd="kernel")
    
    print("Starting OS...")
    qemu_cmd = (
        "qemu-system-riscv64 -M virt "
        "-bios .tmp/fw_jump.bin -kernel kernel/.build/kernel.bin"
    )
    run_cmd(qemu_cmd)

if __name__ == "__main__":
    main()
