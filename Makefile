# Copyright 2026 dywoq - Apache License 2.0
# https://github.com/dywoq/vacui

# Manage toolset
CONFIG ?= i386
include config/$(CONFIG).mk

all: bal
clean: bal_clean
