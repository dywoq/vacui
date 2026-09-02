_______________________________________________________________________________

                            A toolchains folder

This folder contains toolchain files, following the TOML configuration format. 
They have a set of templates that work with specific toolchains. Below, you 
can see an example:

    toolchains/x86_64-linux.toml: 
        templates/x86_64-linux-program.mk
        templates/x86_64-linux-library.mk

Toolchains are specifically made to be working with `victrus`, which is a C/C++
build orchestrator. 
