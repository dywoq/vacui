# Copyright 2026 dywoq - Apache License 2.0
# https://github.com/dywoq/vacui

# Manage toolset
TOOLSET ?= i386
include toolset/$(TOOLSET).mk

all:
	make -C bal/$(TOOLSET)

clean:
	make clean -C bal/$(TOOLSET)
