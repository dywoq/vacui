# Copyright 2026 dywoq - Apache License 2.0
# A part of https://github.com/dywoq/zero

import argparse
import os
from pathlib import Path

CLEAN_PATTERNS = {".cache", ".build", ".config", ".config.old", "compile_commands.json"}


def clean_directory(base_path: Path) -> None:
    import shutil
    dirs_to_remove = []
    try:
        for root, dirs, files in os.walk(base_path, topdown=False):
            root_path = Path(root)
            for d in dirs:
                if d in CLEAN_PATTERNS:
                    dirs_to_remove.append(root_path / d)
            for f in files:
                if f in CLEAN_PATTERNS:
                    try:
                        (root_path / f).unlink()
                        print(f"Removed file: {root_path / f}")
                    except PermissionError:
                        print(f"Error: Permission denied removing file: {root_path / f}")
                    except Exception as e:
                        print(f"Error removing file {root_path / f}: {e}")
        for d in dirs_to_remove:
            try:
                shutil.rmtree(d)
                print(f"Removed directory: {d}")
            except PermissionError:
                print(f"Error: Permission denied removing directory: {d}")
            except Exception as e:
                print(f"Error removing directory {d}: {e}")
    except Exception as e:
        print(f"Error walking directory tree: {e}")


def main() -> None:
    parser = argparse.ArgumentParser(
        prog="clean.py",
        description=f"Clean {CLEAN_PATTERNS} files and directories recursively."
    )
    parser.parse_args()
    clean_directory(Path("."))


if __name__ == "__main__":
    main()
