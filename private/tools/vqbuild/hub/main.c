/*
    Copyright 2026 dywoq - Apache License 2.0
    https://github.com/dywoq/vacui

    Description;

        The vqbuild startup code
*/

#include <errno.h>
#include <stdio.h>
#include <vqbconf.h>

int
main()
{

    /*
     * Allocate a configuration parser
     */
    VQBCONF_PARSER_GUARD(configParser);
    if (!configParser)
    {
        fprintf(
            stderr, "Failed to allocate a pointer to VQBCONF_PARSER data.\n"
        );
        return 1;
    }

    /*
     * Open file and store its stream pointer
     * inside the configParser
     */
    const char *fileName = "VQBUILD";
    FILE *fileStream     = nullptr;
    fileStream           = fopen("VQBUILD", "r");
    if (errno != 0)
    {
        fprintf(
            stderr, "Failed to read \"%s\" file (errno: %d)\n", fileName, errno
        );
        return 1;
    }

    if (!VqbConfParserSetFStream(configParser, fileStream))
    {
        fprintf(stderr, "Failed to store a file stream pointer\n");
        return 1;
    }

    /*
     * Freeing-memory routine
     */
    fclose(fileStream);

    return 0;
}
