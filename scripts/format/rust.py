# Copyright 2026 dywoq - Apache License 2.0
# A part of https://github.com/dywoq/zero

import subprocess
from pathlib import Path


def find_cargo_dirs(root: Path) -> list[Path]:
    return sorted(root.glob("**/Cargo.toml"))


def format_project(cargo_path: Path) -> None:
    project_dir = cargo_path.parent
    print(f"Formatting {project_dir}")
    subprocess.run(["cargo", "clippy", "--fix", "--allow-dirty"], cwd=project_dir, check=True)


def main() -> None:
    root = Path(__file__).parent.parent.parent
    cargo_paths = find_cargo_dirs(root)
    for path in cargo_paths:
        format_project(path)


if __name__ == "__main__":
    main()
