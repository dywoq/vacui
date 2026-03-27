# Copyright 2026 dywoq - Apache License 2.0
# A part of https://github.com/dywoq/zero

import subprocess
import sys
from pathlib import Path


def find_c_files(root: Path) -> list[Path]:
    patterns = ["**/*.h", "**/*.c"]
    files = []
    for pattern in patterns:
        files.extend(root.glob(pattern))
    return sorted(files)


def check_formatting(file_path: Path) -> tuple[int, str]:
    result = subprocess.run(
        ["clang-format", "--dry-run", "--Werror", str(file_path)],
        capture_output=True,
        text=True,
    )
    return result.returncode, result.stdout + result.stderr


def main() -> None:
    root = Path(__file__).resolve().parent.parent.parent
    files = find_c_files(root)

    if not files:
        print("No .c/.h files found")
        return

    failed = False
    for f in files:
        returncode, output = check_formatting(f)

        if output.strip():
            print(output)

        if returncode != 0:
            failed = True

    if failed:
        sys.exit(1)


if __name__ == "__main__":
    main()
