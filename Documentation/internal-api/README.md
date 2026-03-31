This folder contains the documentation for internal API.

# Structure
The `internal-api` folder mirrors the headers structure:
- For shared headers (in `shared/include`)
```
include/      -> Documentation/
-- foo/       -> -- internal-api/
-- -- xyz.hxx -> -- -- foo/
              -> -- -- -- xyz.md
```
- For subsystem headers:
```
boot/load/         -> Documentation/internal-api/
-- include/        -> -- boot-load/
-- -- bios/        -> -- -- bios/
-- -- -- video.hxx -> -- -- -- video.md
```
# Navigation
## Subsystem
- [Boot Load stage (boot/load)](./boot-load/README.md)