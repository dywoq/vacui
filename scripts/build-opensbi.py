#!/usr/bin/env python3

# Copyright 2026 BellusTM - Apache License 2.0
# A part of https://github.com/bellustm/vacui

import argparse
import os
import shutil
import subprocess
import sys

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
ROOT_DIR = os.path.dirname(SCRIPT_DIR)
TMP_DIR = os.path.join(ROOT_DIR, ".tmp")
OPENSBI_REPO = "https://github.com/riscv-software-src/opensbi.git"
OPENSBI_BRANCH = "release-1.8.x"
OPENSBI_PLATFORM = "generic"
TOOLCHAIN_PREFIX = "riscv64-linux-gnu-"
OUTPUT_FILENAME = "fw_jump.bin"
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
    parser = argparse.ArgumentParser(description="Build OpenSBI for RISC-V")
    parser.add_argument(
        "--repo",
        default=OPENSBI_REPO,
        help=f"Git repository URL (default: {OPENSBI_REPO})",
    )
    parser.add_argument(
        "--branch",
        default=OPENSBI_BRANCH,
        help=f"Git branch to checkout (default: {OPENSBI_BRANCH})",
    )
    parser.add_argument(
        "--platform",
        default=OPENSBI_PLATFORM,
        help=f"Platform to build for (default: {OPENSBI_PLATFORM})",
    )
    parser.add_argument(
        "--toolchain",
        default=TOOLCHAIN_PREFIX,
        help=f"Cross-compiler prefix (default: {TOOLCHAIN_PREFIX})",
    )
    parser.add_argument(
        "--output",
        default=TMP_DIR,
        help=f"Output directory for {OUTPUT_FILENAME} (default: {TMP_DIR})",
    )
    parser.add_argument(
        "--clean", action="store_true", help="Remove source directory after build"
    )
    parser.add_argument(
        "--workers", default=WORKERS_COUNT, help="Count of workers in Makefile (default: {WORKERS_COUNT})"
    )
    return parser.parse_args()


def main():
    args = parse_args()

    os.makedirs(args.output, exist_ok=True)

    clone_dir = os.path.join(args.output, "opensbi-src")
    build_firmware = os.path.join(clone_dir, "build", "platform", args.platform, "firmware", OUTPUT_FILENAME)
    output_path = os.path.join(args.output, OUTPUT_FILENAME)

    if os.path.exists(clone_dir):
        print(f"Updating existing repository: {clone_dir}")
        run_cmd("git fetch origin", cwd=clone_dir)
        run_cmd(f"git checkout {args.branch}", cwd=clone_dir)
        run_cmd(f"git pull origin {args.branch}", cwd=clone_dir)
    else:
        print(f"Cloning repository: {args.repo}")
        ret = run_cmd(
            f"git clone -b {args.branch} --single-branch {args.repo} {clone_dir}"
        )
        if ret != 0:
            print("Failed to clone repository")
            sys.exit(1)

    print(f"Building OpenSBI for platform: {args.platform}...")
    env = os.environ.copy()
    env["CROSS_COMPILE"] = args.toolchain
    ret = run_cmd(
        f"make PLATFORM={args.platform} -j{args.workers}",
        cwd=clone_dir,
        env=env,
    )
    if ret != 0:
        print("Failed to build OpenSBI")
        sys.exit(1)

    if os.path.exists(build_firmware):
        shutil.copy2(build_firmware, output_path)
        print(f"{OUTPUT_FILENAME} copied to: {output_path}")
    else:
        print(f"{OUTPUT_FILENAME} not found after build")
        sys.exit(1)

    if args.clean and os.path.exists(clone_dir):
        shutil.rmtree(clone_dir)
        print(f"Removed source directory: {clone_dir}")

    print("Build complete!")


if __name__ == "__main__":
    main()
