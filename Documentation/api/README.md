# Description
This directory contains the documentation of headers API. Its structure is aligned with the headers from `include`folder and header symbols. For example:

- Header directory:
```
include/
-- foo/
-- -- xyz.h
```
- Documentation directory:
```
Documentation/
-- api 
-- -- foo/
-- -- -- xyz.md
```
It also works with sub-modules.

# Navigation
## Boot loader
- [`zero/boot/info.h`](./boot/info)
## Drivers
### Video
- [`zero/drvs/vid/color.h`](./drvs/vid/color)
- [`zero/drvs/vid/iface.h`](./drvs/vid/iface)
