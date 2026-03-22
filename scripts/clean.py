# Copyright 2026 dywoq - Apache License 2.0
# A part of https://github.com/dywoq/zero

import argparse
import os
from pathlib import Path

CLEAN_PATTERNS = {".cache", ".build", ".config", ".config.old"}


def clean_directory(base_path: Path) -> None:
    import shutil
    dirs_to_remove = []
    for root, dirs, files in os.walk(base_path, topdown=False):
        root_path = Path(root)
        for d in dirs:
            if d in CLEAN_PATTERNS:
                dirs_to_remove.append(root_path / d)
        for f in files:
            if f in CLEAN_PATTERNS:
                (root_path / f).unlink()
                print(f"Removed file: {root_path / f}")
    for d in dirs_to_remove:
        shutil.rmtree(d)
        print(f"Removed directory: {d}")


def main() -> None:
    parser = argparse.ArgumentParser(
        prog="clean.py",
        description="Clean .cache, .build, .config, and .config.old files and directories recursively."
    )
    parser.parse_args()
    clean_directory(Path("."))


if __name__ == "__main__":
    main()
