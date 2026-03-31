The `zero/boot/info.hxx` is a part of Boot Load Stage. It contains a thin wrappers around BIOS video services, which means it doesn't validate your inputs.

All header symbols go into `zero::boot::bios` namespace.
# Symbols
## `SetVideoMode`
**Signature**:
```cpp
namespace zero::boot::bios
{
	void
	SetVideoMode(UWord mode);
}
```
**Description**:
Calls a video services BIOS interruption. The form:
- `AH`: 0
- `AX`: `mode`
Internally, it sets the current video mode to `mode`. It's important for `GetVideoMode`.

**Parameters**:
- `mode`: New video mode.

## `GetVideoMode`
**Signature**:
```cpp
namespace zero::boot:bios {
	UWord
	GetVideoMode();
}
```
**Description**:
Returns the current video mode. If `SetVideoMode` wasn't called, the default value is `0x03`. 