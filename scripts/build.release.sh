# Copyright 2026 dywoq - Apache License 2.0
# A part of https://github.com/dywoq/zero
#
# The project is not associated with Nintendo Co., Ltd.

rm build -fr
rm compile_commands.json -fr
catnip release -T 3DS
mv build/main.release/compile_commands.json ./
3dsxtool build/main.release/zero.elf build/main.release/zero.3dsx
