#include <vqbconf.h>
#define STB_DS_IMPLEMENTATION
#include <stb_ds.h>
#include <stddef.h>

typedef struct _VQBCONF__MAP_DATA
{
    char *key;
    char *value;
} VQBCONF__MAP_DATA;

struct _VQBCONF_MAP
{
    VQBCONF__MAP_DATA *MapData;
};

VQBCONF_MAP *
VqbConfAllocMap(void)
{
    VQBCONF_MAP *configMapPtr = malloc(sizeof(VQBCONF_MAP));
    if (!configMapPtr)
    {
        return nullptr;
    }
    configMapPtr->MapData = nullptr;
    sh_new_arena(configMapPtr->MapData);
    return configMapPtr;
}

void
VqbConfDestroyMap(VQBCONF_MAP *ConfigMapPtr)
{
    if (!ConfigMapPtr)
    {
        return;
    }
    shfree(ConfigMapPtr->MapData);
    free(ConfigMapPtr);
    ConfigMapPtr = nullptr;
}

bool
VqbConfMapGet(
    VQBCONF_MAP *ConfigMapPtr,
    const char *KeyPtr,
    char **ValueDestinationPtr
)
{
    if (!ValueDestinationPtr || !KeyPtr || !ConfigMapPtr)
    {
        return false;
    }

    if (!VqbConfMapExists(ConfigMapPtr, KeyPtr))
    {
        return false;
    }

    char *foundValue     = shget(ConfigMapPtr->MapData, KeyPtr);
    *ValueDestinationPtr = foundValue;
    return true;
}

bool
VqbConfMapPut(
    VQBCONF_MAP *ConfigMapPtr,
    char *KeyPtr,
    char *ValuePtr
)
{
    if (!ConfigMapPtr || !KeyPtr)
    {
        return false;
    }

    if (VqbConfMapExists(ConfigMapPtr, KeyPtr))
    {
        return false;
    }

    shput(ConfigMapPtr->MapData, KeyPtr, ValuePtr);
    return true;
}

bool
VqbConfMapExists(
    VQBCONF_MAP *ConfigMapPtr,
    const char *KeyPtr
)
{
    if (!ConfigMapPtr || !KeyPtr)
    {
        return false;
    }
    ptrdiff_t index = shgeti(ConfigMapPtr->MapData, KeyPtr);
    return index != -1;
}

bool
VqbConfMapIterate(
    VQBCONF_MAP *ConfigMapPtr,
    VQBCONF_MAP_ITERATOR_FUNC IteratorFuncPtr
)
{
    if (!ConfigMapPtr || !IteratorFuncPtr)
    {
        return false;
    }

    for (ptrdiff_t index = 0; index < shlen(ConfigMapPtr->MapData); ++index)
    {
        bool continueOrNot = IteratorFuncPtr(
            index,
            &ConfigMapPtr->MapData[index].key,
            &ConfigMapPtr->MapData[index].value
        );

        if (!continueOrNot)
        {
            break;
        }
    }

    return true;
}
