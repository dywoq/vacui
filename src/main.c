// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero
//
// The project is not associated with Nintendo Co., Ltd.

#include <3ds.h>

int main() {
    gfxInitDefault();
    consoleInit(GFX_TOP, nullptr);

    while (aptMainLoop()) {
        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }
    gfxExit();
    return 0;
}
