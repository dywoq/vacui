#
# Copyright 2026 dywoq - Apache License 2.0
# https://github.com/dywoq/vacui
#
# Description:
#
# 	Cross-compiler Makefile definitions, that automatically
# 	and statically set the compiler, depending on ARCH.
#	It's specifically suited for bare-metal development.
#
#	The makefile definition is going to report an error about
#	wrong architecture value.
#
#	It's assuming you're using GNU compiler colleciton.
#
# Architecture values (ARCH):
#
# 	- amd64
#	- aarch64
#

ARCH_CORRECT := false
ARCH_EXPECTED := "amd64 aarch64"
ifeq ($(ARCH), amd64)
	CC := gcc
	CXX := g++
	OBJCOPY := objcopy
	LD := ld
	ARCH_CORRECT := true
endif

ifeq ($(ARCH), aarch64)
	CC := aarch64-linux-gnu-gcc
	CXX := aarch64-linux-gnu-g++
	OBJ_COPY := aarch64-linux-gnu-objcopy
	LD := aarch64-linux-gnu-ld
	ARCH_CORRECT := true
endif

ifeq ($(ARCH_CORRECT), false)
	$(error Wrong ARCH value: $(ARCH). Expected: $(ARCH_EXPECTED))
endif

