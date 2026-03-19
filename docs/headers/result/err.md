# Description
The `result/error.h` defines error codes and `result_error` structure.

# Symbols
## `result_err_code`

**Signature**:
```c
enum result_error_code : ubyte_t {
    RESULT_ERR_OK = 0,
    RESULT_ERR_FAILED = 1,
    RESULT_ERR_NULL_PTR = 2,
};
```
**Description**: Result error codes, whose integers take 1 byte.
**Values**:
- `RESULT_ERR_OK`: The operation successfully passed.
- `RESULT_ERR_FAILED`: Something failed.
- `RESULT_ERR_NULL_PTR`: Null pointer, therefore the operation can't proceed.

## `result_err`
**Signature**:
```c
struct [[gnu::packed]] result_err {
    const char *additional;
    enum result_err_code code;
};
```
**Description**: A result error structure. It can contain additional context, but the error code is always used and filled to know whether it's an error or not.

If `code` field is not `RESULT_ERR_OK`, then it's an error. Otherwise it's not.

The structure is used to provide additional context of the error. However, it's not recommended to use it heavily, since the stack is limited. Use enumeration `result_err_code` for errors without additional context.

**Fields**:
- `additional`: Additional optional context. Can be `nullptr`.
- `code`: An error code, which is necessary to fill.
## `RESULT_IS_ERR`
**Signature**:
```c
#define RESULT_IS_ERR(err)
```
**Description**: Checks if `err` parameter is error by comparing it to `RESULT_ERR_OK`.
**Parameters**:
- `err`: An error code to check. Must be type of `result_err_code`.

## `RESULT_IS_OK`
**Signature**:
```c
#define RESULT_IS_OK(err)
```
**Description**: Checks if `err` parameter is not error by comparing it to `RESULT_ERR_OK`.
**Parameters**:
- `err`: An error code to check. Must be type of `result_err_code`.
## `RESULT_NEW`
**Signature**:
```
#define RESULT_NEW(num, str)                                       \
    (struct result_err) { .additional = str, .code = num }
```
**Description**: A shortcut way of creating `result_err` object.
**Parameters**;
- `num`: An error code.
- `str`:  Additional context. Can be `nullptr`.