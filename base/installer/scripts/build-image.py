#!/usr/bin/python3
# Copyright 2026 dywoq - Apache License 2.0
# A part of https://github.com/dywoq/vacui

import argparse
import subprocess

BOOT_SECTOR_DIR = "boot/sector"
BOOT_PRIMARY_DIR = "boot/primary"
IMAGE_FILE = ".build/vqinstaller.img"


def run_cmd(cmd: list[str], cwd: str | None = None) -> None:
    result = subprocess.run(cmd, cwd=cwd, check=True)
    if result.returncode != 0:
        raise RuntimeError(f"Command failed: {' '.join(cmd)}")


def main():
    parser = argparse.ArgumentParser(
        prog="build-image.py",
        description="Build the Vacui VQ installer, which results in vqinstaller.img file",
    )
    parser.parse_args()

    print("Building")
    run_cmd(["make", "clean", "all", "-C", BOOT_SECTOR_DIR])
    run_cmd(["make", "clean", "all", "-C", BOOT_PRIMARY_DIR])
    run_cmd(["xmake"])
    run_cmd(
        [
            "objcopy",
            "-O",
            "binary",
            ".build/linux/x86_64/release/installer",
            ".build/installer.bin",
        ]
    )

    sector_bin = f"{BOOT_SECTOR_DIR}/.build/sector.bin"
    load_bin = f"{BOOT_PRIMARY_DIR}/.build/primary.bin"
    installer_bin = ".build/installer.bin"

    print(f"Creating image \"{IMAGE_FILE}\"")
    run_cmd(["dd", "if=/dev/zero", "of=" + IMAGE_FILE, "bs=1M", "count=10"])
    run_cmd(["dd", "if=" + sector_bin, "of=" + IMAGE_FILE, "bs=512", "count=1", "conv=notrunc"])
    run_cmd(["dd", "if=" + load_bin, "of=" + IMAGE_FILE, "bs=512", "seek=1", "conv=notrunc"])
    run_cmd(["dd", "if=" + installer_bin, "of=" + IMAGE_FILE, "bs=512", "seek=2", "conv=notrunc"])

if __name__ == "__main__":
    main()
