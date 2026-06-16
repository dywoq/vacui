______________________________________________________________________________
                                Vacui

Vacui is an operating system, designed to support multiple architectures,
using Abstraction layers. These layers talk to each other through layers
always:

    AAL (Architecture Abstraction Layer) - Hides the architecture-dependent
    code.

    PAL (Platform Abstraction Layer) - Hides the platform-specific details.

    BAL (Boot Abstraction Layer) - The first entry point of Vacui, loading
    generic kernel from disk and executing it, handing over control.

Current supported architectures:

    x86-64

______________________________________________________________________________
                                Contact

Lead maintainer:
- dywoq:
    dywoq.contact@gmail.com
    github.com/dywoq

