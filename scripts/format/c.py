# Copyright 2026 dywoq - Apache License 2.0
# A part of https://github.com/dywoq/zero

import subprocess
from pathlib import Path


def find_c_files(root: Path) -> list[Path]:
    patterns = ["**/*.h", "**/*.c"]
    files = []
    for pattern in patterns:
        files.extend(root.glob(pattern))
    return sorted(files)


def format_file(file_path: Path) -> None:
    subprocess.run(["clang-format", "-i", str(file_path)], check=True)


def main() -> None:
    root = Path(__file__).parent.parent.parent
    files = find_c_files(root)
    for f in files:
        format_file(f)


if __name__ == "__main__":
    main()
