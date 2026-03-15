# Copyright 2026 dywoq - Apache License 2.0
# A part of https://github.com/dywoq/zero
#
# The project is not associated with Nintendo Co., Ltd.

rm build -fr
rm compile_commands.json -fr
catnip debug -T 3DS
mv build/main.debug/compile_commands.json ./
3dsxtool build/main.debug/zero.elf build/main.debug/zero.3dsx
