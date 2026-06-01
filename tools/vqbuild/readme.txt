            vqbuild

The vqbuild - is a C/C++ build orchestrator. It reads 'config' file in target
directory and gives its parameters to Make, which handles the compilation
and linking target.

            Building

To build vqbuild, you need to have installed:
- GNU Make
- binutils
- GCC compiler

After you installed them, go to tools/vqbuild directory and run:

        make all

The binary will be in new .build directory.
