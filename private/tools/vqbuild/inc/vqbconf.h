/*
    Copyright 2026 dywoq - Apache License 2.0
    https://github.com/dywoq/vacui

    Description:

        Configuration parsing and management
*/

#ifndef _VQBCONF_H
#define _VQBCONF_H

#include <stb_ds.h>
#include <stddef.h>
#include <stdio.h>

/*
    Description:

        Configuration parser.

        It's responsible for parsing the configs and returning
        a map with their keys and values.
*/
typedef struct _VQBCONF_PARSER VQBCONF_PARSER;

/*
    Description:

        Allocates a memory for the VQBCONF_PARSER struct data,
        and returns a pointer to it.

        Returns null if allocating failed.
*/
VQBCONF_PARSER *
VqbConfAllocParser(void);

/*
    Description:

        Frees a pointer to VQBCONF_PARSER struct data.
        setting it to null. This function doesn't free automatically
        pointers, stored by user.

        Returns if it's null.

    Parameters:

        - ParserPtr: The pointer to free.
*/
void
VqbConfDestroyParser(VQBCONF_PARSER *ParserPtr);

static inline void
VqbConf__GuardCleanupParser(VQBCONF_PARSER **Parser)
{
    VqbConfDestroyParser(*Parser);
}
/*
    Description:

        A macro guard which allocates a pointer to VQBCONF_PARSER data,
        and destroys the pointer when the variable goes out of scope.
*/
#define VQBCONF_PARSER_GUARD(variableName)              \
    [[gnu::cleanup(VqbConf__GuardCleanupParser)]]       \
    VQBCONF_PARSER *variableName = VqbConfAllocParser()

/*
    Description:

        Sets a pointer to the file stream within a pointer to
        VQBCONF_PARSER struct data. Returns false if:
        - ParserPtr is null;
        - FileStream is null;
        - The underlying lock flag is on.

    Parameters:

        - ParserPtr: The pointer to VQBCONF_PARSER struct data.
        - FileStream: The pointer to file stream, stored inside the
        config parser data.
*/
bool
VqbConfParserSetFStream(
    VQBCONF_PARSER *ParserPtr,
    FILE *FileStream
);

/*
    Description:

        A struct with the configuration keys data.
*/
typedef struct _VQBCONF_MAP VQBCONF_MAP;

/*
    Description:

        An iterator function type definition, specifically made
        for working with the configuration map.
*/
typedef bool (*VQBCONF_MAP_ITERATOR_FUNC)(
    ptrdiff_t Index,
    char **KeyPtr,
    char **ValuePtr
);

/*
    Description:

        Allocates a pointer to VQBCONF_MAP struct data.
        Returns false if the operation failed.
*/
VQBCONF_MAP *
VqbConfAllocMap(void);

/*
    Description:

        Frees a pointer to VQBCONF_MAP struct data. It automatically
        destroys pointers to key name strings in the underlying map.

        Returns if it's null.

    Parameters:

        - ConfigMapPtr: A pointer to VQBCONF_MAP struct data
*/
void
VqbConfDestroyMap(VQBCONF_MAP *ConfigMapPtr);

static inline void
VqbConf__GuardCleanupMap(VQBCONF_MAP **ConfigMapPtr)
{
    VqbConfDestroyMap(*ConfigMapPtr);
}
/*
    Description:

        A macro guard which allocates a pointer to VQBCONF_MAP data,
        and destroys the pointer when the variable goes out of scope.
*/
#define VQBCONF_MAP_GUARD(variableName)           \
    [[gnu::cleanup(VqbConf__GuardCleanupMap)]]    \
    VQBCONF_MAP *variableName = VqbConfAllocMap()

/*
    Description:

        Writes value of a specified key to ValueDestinationPtr.
        Returns false if:
            - ValueDestinationPtr, KeyPtr or ConfigMapPtr is null;
            - key with the given name doesn't exists.

    Parameters:

        - ConfigMapPtr: A pointer to VQBCONF_MAP struct data.

        - KeyPtr: A const pointer to string name of the key.

        - ValueDestinationPtr: A pointer to the value destination buffer.
*/
bool
VqbConfMapGet(
    VQBCONF_MAP *ConfigMapPtr,
    const char *KeyPtr,
    char **ValueDestinationPtr
);

/*
    Description:

        Puts a new key into the map. The configuration map struct is provided
        a memory ownership of KeyPtr pointer.

        Returns false if:
        - ConfigMapPtr or KeyPtr is null;
        - key with given name already exists.

    Parameters:

        - ConfigMapPtr: A pointer to VQBCONF_MAP struct data.

        - KeyPtr: A pointer to the string name of the key.

        - ValuePtr: A pointer to the key value string.
*/
bool
VqbConfMapPut(
    VQBCONF_MAP *ConfigMapPtr,
    char *KeyPtr,
    char *ValuePtr
);

/*
    Description:

        Checks whether a key exists within the configuration map.

    Parameters:

        - ConfigMapPtr: A pointer to VQBCONF_MAP struct data.

        - KeyPtr: A const pointer to the key name string.
*/
bool
VqbConfMapExists(
    VQBCONF_MAP *ConfigMapPtr,
    const char *KeyPtr
);

/*
    Description:

        Iterates over keys and calls IteratorFuncPtr, providing arguments
        to it. Stops if IteratorFuncPtr returns false.

        Returns false if ConfigMapPtr or IteratorFuncPtr is null.
*/
bool
VqbConfMapIterate(
    VQBCONF_MAP *ConfigMapPtr,
    VQBCONF_MAP_ITERATOR_FUNC IteratorFuncPtr
);

#endif
