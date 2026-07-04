/*
    Copyright 2026 dywoq - Apache License 2.0
    https://github.com/dywoq/vacui

    Description;

        The vqbuild startup code
*/

#include <stddef.h>
#include <stdio.h>
#include <vqbconf.h>

static bool
ConfigMapIterator_(
    ptrdiff_t Index,
    char **KeyPtr,
    char **ValuePtr
)
{
    if (Index == 2)
    {
        return false;
    }
    printf("[%zu] -> %s:%s\n", Index, *KeyPtr, *ValuePtr);
    return true;
}

int
main()
{
    VQBCONF_MAP_GUARD(configMap);
    if (!configMap)
    {
        printf("Failed to allocate a pointer to VQBCONF_MAP data\n");
        return 1;
    }

    char value[] = "Hi!";
    VqbConfMapPut(configMap, "tmp", value);
    VqbConfMapPut(configMap, "tmpp", "Hi!");
    VqbConfMapPut(configMap, "hook", "this is a hook");

    if (!VqbConfMapExists(configMap, "tmpsp"))
    {
        printf("tmpsp key doesn't exist\n");
    }

    VqbConfMapIterate(configMap, ConfigMapIterator_);

    return 0;
}
