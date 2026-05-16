            Vacui VQ installer

The Vacui installer installs formats disk and
setups Vacui on disk with important files.

                Parts

The Vacui VQ installer is split into two parts:
- vqinstaller.img:
    This image file contains the logic of installing Vacui.
    It's responsible for formatting disk and copying OS files from ISO
    to the disk.
- vqos_data.iso:
    This ISO file contains the executable of kernel and its bootloader.
    As said in vqinstaller.img, they're unpacked and copied to the disk.