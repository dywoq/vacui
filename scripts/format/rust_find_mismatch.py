# Copyright 2026 dywoq - Apache License 2.0
# A part of https://github.com/dywoq/zero

import subprocess
import sys
from pathlib import Path


def find_cargo_dirs(root: Path) -> list[Path]:
    cargo_files = [f for f in root.rglob("Cargo.toml") if "target" not in f.parts]
    return sorted({f.parent for f in cargo_files})


def run_clippy(cargo_dir: Path) -> tuple[int, str]:
    result = subprocess.run(
        ["cargo", "clippy", "--all-targets", "--", "-D", "warnings"],
        cwd=cargo_dir,
        capture_output=True,
        text=True,
    )
    return result.returncode, result.stdout + result.stderr


def main() -> None:
    root = Path(__file__).resolve().parent.parent.parent
    cargo_dirs = find_cargo_dirs(root)
    
    if not cargo_dirs:
        print("No Cargo.toml found")
        return

    failed = False
    for cargo_dir in cargo_dirs:
        print(f"Checking {cargo_dir}...")
        returncode, output = run_clippy(cargo_dir)
        
        if output.strip():
            print(output)
            
        if returncode != 0:
            failed = True

    if failed:
        sys.exit(1)


if __name__ == "__main__":
    main()
