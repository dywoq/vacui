#include <efi/efi.h>
#include <efi/efilib.h>
#include <init.h>
#include <vacui/boot.h>

EFI_STATUS
efi_main(EFI_HANDLE img_handle, EFI_SYSTEM_TABLE *system_table) {
    InitializeLib(img_handle, system_table);

    Print(L"Hi!\n");

    while (1) {
    }
    return EFI_SUCCESS;
}
