______________________________________________________________________________
                                vqbuild

vqbuild - is a build orchestrator, made specifically for Vacui codebase and
C/C++.

It reads the target config ("module" file), parses it and runs GNU Makefile
to handle compilation of main target (and dependencies if they're listed).

vqbuild is only responsible for orchestrating build process - it doesn't:
- validate module config values
- build dependencies graph

All compilation is handled by Makefile. 

______________________________________________________________________________
                              Requirements

To run any command, make sure you have installed:
- GNU Makefile
- Bear (compile_commands.json generation)

______________________________________________________________________________
                                Contact

Lead maintainer:
- dywoq:
    dywoq.contact@gmail.com
    github.com/dywoq
