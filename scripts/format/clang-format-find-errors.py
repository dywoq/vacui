#!/usr/bin/env python3

# Copyright 2026 dywoq - Apache License 2.0
# A part of https://github.com/dywoq/vacui

import subprocess
from pathlib import Path

EXTENSIONS = {".c", ".cxx", ".h", ".hxx"}

def main():
    root = Path.cwd()
    files = [
        str(file) for file in root.rglob("*")
        if file.is_file() and file.suffix in EXTENSIONS
    ]

    if not files:
        return

    result = subprocess.run(
        ["clang-format", "--dry-run", "--Werror", "--style=file"] + files,
        capture_output=True,
        text=True
    )

    if result.returncode != 0: 
        print("Formatting errors found in the following files:")
        print(result.stderr)
        exit(1)

if __name__ == "__main__":
    main()
