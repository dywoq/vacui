 # Copyright 2026 dywoq - Apache License 2.0
# A part of https://github.com/dywoq/zero

import argparse
import os
import subprocess
import shutil

BUILD_DIR = ".build"
BOOT_SECTOR_DIR = "boot/sector"
BOOT_LOAD_DIR = "boot/load"
IMAGE_FILE = f"{BUILD_DIR}/zero.img"


def run_cmd(cmd: list[str], cwd: str | None = None) -> None:
    result = subprocess.run(cmd, cwd=cwd, check=True)
    if result.returncode != 0:
        raise RuntimeError(f"Command failed: {' '.join(cmd)}")


def main():
    parser = argparse.ArgumentParser(
        prog="image.py",
        description="Build boot sector, boot loader, kernel and create a disk image."
    )
    parser.parse_args()
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.dirname(script_dir)
    os.chdir(project_root)

    if os.path.exists(BUILD_DIR):
        shutil.rmtree(BUILD_DIR)
    os.makedirs(BUILD_DIR)

    print("Building boot sector...")
    run_cmd(["make", "clean", "all", "-C", BOOT_SECTOR_DIR])

    print("Building boot loader...")
    run_cmd(["make", "clean", "all", "-C", BOOT_LOAD_DIR])

    sector_bin = f"{BOOT_SECTOR_DIR}/{BUILD_DIR}/sector.bin"
    load_bin = f"{BOOT_LOAD_DIR}/{BUILD_DIR}/load.bin"
    
    print(f"Creating image: {IMAGE_FILE}")
    run_cmd(["dd", "if=/dev/zero", "of=" + IMAGE_FILE, "bs=1M", "count=10"])
    run_cmd(["dd", "if=" + sector_bin, "of=" + IMAGE_FILE, "bs=512", "count=1", "conv=notrunc"])
    run_cmd(["dd", "if=" + load_bin, "of=" + IMAGE_FILE, "bs=512", "seek=1", "conv=notrunc"])

    print("Done!")


if __name__ == "__main__":
    main()
