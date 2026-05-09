// Copyright dywoq 2026 - Apache License 2.0
// https://github.com/dywoq/vacui

__asm(".code16gcc");

#include <vacui/primary/bios.h>

static unsigned char code_ = 0;

__bios bool bios_disk_extread(struct bios_dpa *dpa, unsigned char drive)
{
  if (!dpa)
    return false;
  bool cf;
  unsigned short code;
  __asm volatile("int $0x13\n"
                 : "=@ccc"(cf), "=a"(code)
                 : "a"((0x42 << 8)), "S"(dpa), "d"(drive)
                 : "cc", "memory");
  if (cf)
    bios_disk_setstatus((unsigned char)code >> 8);
  return !cf;
}

__bios void bios_disk_setstatus(unsigned char code) { code_ = code; }

__bios unsigned char bios_disk_getstatus() { return code_; }
