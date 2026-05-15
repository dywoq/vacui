#include <vqboot.h>

void
pre(struct boot_info *info)
{ 
    
    while (true)
        __asm volatile("hlt\n");
}
