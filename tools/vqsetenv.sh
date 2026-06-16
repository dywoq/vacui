#!/usr/bin/bash

# Copyright 2026 dywoq - Apache License 2.0
# https://github.com/dywoq/vacui

# Sets environment variables that make it easier to access
# Vacui source code content, without using relative paths.
# 
# You must run this script from the root directory of Vacui:
# 
# cd vacui
# ./tools/vqsetenv.sh

export VQ=$PWD
export VQBASE=$VQ/base
