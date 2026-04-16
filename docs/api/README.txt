        == Documentation of internal API ==

The folder contains the documentation of internal API and
headers.

                == Structure ==

The structure of documentation of internal API mirrors
the OS part's 'include' directory:

from

| - <part of OS>/
| - - <subsystem>/
| - - - include/
| - - - - vacui/
| - - - - - <part of OS>/
| - - - - - - <subsystem>/
| - - - - - - - <header>.h

to

| docs/
| - api/
| - - <part of OS>/
| - - - <subsystem>/
| - - - - <header>.h

This works recursively.

The only exception is a directory 'shared', which has the documentation
of the shared headers in the root's include directory.
