/*
 * Copyright 2026 dywoq - Apache License 2.0
 * https://github.com/dywoq/vacui
 *
 * An implementation of HubPanic function from 'vqinsthub.h'.
 */

#include <vqinstmetadata.h>
#include <vqinstprint.h>
#include <vqinstval.h>

[[noreturn]]
void
HubPanic(const char *message)
{
    PrintSetFgColor(VAL_BRIGHT_WHITE);
    PrintSetBgColor(VAL_GREEN);
    PrintClearScreen();

    USIZE row = 1;
    USIZE maximumColumns = ValGetColumns();

    const char *totalMessage = message ? message : "<null message>";
    PrintStrFixed(totalMessage, row, 1);

    row += 2;
    for (USIZE column = 1; column < maximumColumns - 1; column++)
    {
        if (column == 1 || column == maximumColumns - 2)
        {
            PrintCharFixed('|', row, column);
            continue;
        }
        PrintCharFixed('-', row, column);
    }

    row += 2;
    PrintStrFixed("The installer panicked and cannot continue.", row, 1);

    row += 16;
    PrintStrFixed(MetadataGetTitle(), row, 1);
    row++;
    PrintStrFixed(MetadataGetBuildType(), row, 1);
    row++;
    PrintStrFixed(MetadataGetVersion(), row, 1);

    while (true)
        ;
}
