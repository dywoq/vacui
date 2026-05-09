// Copyright dywoq 2026 - Apache License 2.0
// https://github.com/dywoq/vacui

#include <vacui/primary/bios.h>

__bios unsigned char bios_disk_getstatus(unsigned char drive)
{
  unsigned char dest;
  __asm volatile("int $0x13\n"
                 : "=a"(dest)
                 : "a"(0x01 << 8), "d"(drive)
                 : "cc", "memory");
  return (dest & (0xFF << 8)) >> 8;
}

__bios bool bios_disk_extread(struct bios_dpa *dpa, unsigned char drive)
{
  if (!dpa)
    return false;

  bool cf;
  __asm volatile("int $0x13\n"
                 : "=@ccc"(cf)
                 : "a"((0x42 << 8)), "S"(dpa), "d"(drive)
                 : "cc", "memory");
  return !cf;
}
