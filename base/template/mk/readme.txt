______________________________________________________________________________
                        Makefile templates

This folder contains the Makefile templates, which are used along with 
vqbuild and within Vacui OS source code.

______________________________________________________________________________
                Must-support architectures/compilers

The Makefile templates in this directory must support the following
architectures and use these compilers:

    x86-64:
        - C compiler:   x86_64-linux-gnu-g++
        - Object copy:  x86_64-linux-gnu-objcopy
        - C++ compiler: x86_64-linux-gnu-g++
        - Linker:		x86_64-linux-gnu-ld
