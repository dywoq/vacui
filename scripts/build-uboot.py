#!/usr/bin/env python3

# Copyright 2026 dywoq - Apache License 2.0
# A part of https://github.com/dywoq/vacui

import argparse
import os
import shutil
import subprocess
import sys

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
ROOT_DIR = os.path.dirname(SCRIPT_DIR)
TMP_DIR = os.path.join(ROOT_DIR, ".tmp")
UBOOT_REPO = "https://github.com/u-boot/u-boot.git"
UBOOT_BRANCH = "master"
WORKERS_COUNT = "1"

def run_cmd(cmd, cwd=None, env=None, capture=True):
    if capture:
        result = subprocess.run(
            cmd,
            shell=True,
            cwd=cwd,
            env=env,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
        )
        print(result.stdout.decode())
        return result.returncode
    return subprocess.call(cmd, shell=True, cwd=cwd, env=env)


def parse_args():
    parser = argparse.ArgumentParser(description="Build U-Boot for RISC-V")
    parser.add_argument(
        "--repo", default=UBOOT_REPO, help=f"Git repository URL (default: {UBOOT_REPO})"
    )
    parser.add_argument(
        "--branch",
        default=UBOOT_BRANCH,
        help=f"Git branch to checkout (default: {UBOOT_BRANCH})",
    )
    parser.add_argument(
        "--defconfig",
        default="qemu-riscv64_smode_defconfig",
        help="Defconfig for RISC-V board (default: qemu-riscv64_smode_defconfig)",
    )
    parser.add_argument(
        "--toolchain",
        default="riscv64-linux-gnu-",
        help="Cross-compiler prefix (default: riscv64-linux-gnu-)",
    )
    parser.add_argument(
        "--clean", action="store_true", help="Clean build directory before building"
    )
    parser.add_argument(
        "--output",
        default=TMP_DIR,
        help=f"Output directory for uboot.bin (default: {TMP_DIR})",
    )
    parser.add_argument(
        "--workers",
        default=WORKERS_COUNT,
        help=f"Workers for building UBoot (default: {WORKERS_COUNT})"
    )
    return parser.parse_args()


def main():
    args = parse_args()

    os.makedirs(args.output, exist_ok=True)

    build_dir = os.path.join(TMP_DIR, "u-boot-build")
    clone_dir = os.path.join(TMP_DIR, "u-boot-src")

    if args.clean and os.path.exists(clone_dir):
        shutil.rmtree(clone_dir)

    if not os.path.exists(clone_dir):
        print(f"Cloning repository: {args.repo}")
        ret = run_cmd(f"git clone --depth 1 -b {args.branch} {args.repo} {clone_dir}")
        if ret != 0:
            print("Failed to clone repository")
            sys.exit(1)
    else:
        print(f"Updating existing repository: {clone_dir}")
        run_cmd("git fetch origin", cwd=clone_dir)
        run_cmd(f"git checkout {args.branch}", cwd=clone_dir)
        run_cmd(f"git pull origin {args.branch}", cwd=clone_dir)

    os.makedirs(build_dir, exist_ok=True)

    print(f"Configuring U-Boot with {args.defconfig}...")
    ret = run_cmd(f"make {args.defconfig}", cwd=clone_dir)
    if ret != 0:
        print("Failed to configure U-Boot")
        sys.exit(1)

    print(f"Building U-Boot for RISC-V...")
    env = os.environ.copy()
    env["CROSS_COMPILE"] = args.toolchain
    ret = run_cmd(f"make -j${args.workers}", cwd=clone_dir, env=env)
    if ret != 0:
        print("Failed to build U-Boot")
        sys.exit(1)

    uboot_bin_src = os.path.join(clone_dir, "u-boot.bin")
    uboot_bin_dst = os.path.join(args.output, "uboot.bin")

    if os.path.exists(uboot_bin_src):
        shutil.copy2(uboot_bin_src, uboot_bin_dst)
        print(f"uboot.bin copied to: {uboot_bin_dst}")
    else:
        print("uboot.bin not found after build")
        sys.exit(1)

    if args.clean and os.path.exists(clone_dir):
        shutil.rmtree(clone_dir)
        print(f"Removed source directory: {clone_dir}")

    if args.clean and os.path.exists(build_dir):
        shutil.rmtree(build_dir)
        print(f"Removed build directory: {build_dir}")

    print("Build complete!")


if __name__ == "__main__":
    main()
