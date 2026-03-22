# Copyright 2026 dywoq - Apache License 2.0
# A part of https://github.com/dywoq/zero

import argparse
from pathlib import Path

CLEAN_PATTERNS = {".cache", ".build", ".config", ".config.old"}


def clean_directory(base_path: Path) -> None:
    for entry in base_path.iterdir():
        if entry.name in CLEAN_PATTERNS:
            if entry.is_dir():
                import shutil
                shutil.rmtree(entry)
                print(f"Removed directory: {entry}")
            else:
                entry.unlink()
                print(f"Removed file: {entry}")


def main() -> None:
    parser = argparse.ArgumentParser(
        prog="clean.py",
        description="Clean .cache, .build, .config, and .config.old files and directories recursively."
    )
    parser.parse_args()
    clean_directory(Path("."))


if __name__ == "__main__":
    main()
