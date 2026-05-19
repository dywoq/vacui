#include <vqstlstr.h>

[[nodiscard]]
STLSTR_ERROR
StlGetStringLen(
    USIZE *destLen,
    const char *str
)
{
    if (!destLen)
        return STLSTR_NULL_DEST_LEN;
    if (!str)
        return STLSTR_NULL_STR;
    for (const char *p = str; *p != '\0'; ++p)
        *destLen += 1;
    return STLSTR_OK;
}
