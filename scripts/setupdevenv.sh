#!/usr/bin/bash
#
# Copyright 2026 dywoq - Apache License 2.0
# https://github.com/dywoq/vacui
#
# Module Description
#
#       This bash script is responsible for setting up development 
#       environment. It compiles the host OS development tools and puts 
#       them into .devenv/bin folder, which is added to the path. This script
#       must be executed every session.
# 
#       It must be ran as:
# 
#           source scripts/setupdevenv.h
#

#
# Create the .devenv/bin directory
# 

export DEVENV_BIN=.devenv/bin
mkdir $DEVENV_BIN -p

#
# Compile the host OS tools
# 

cd tools/victus && go build . && cd ../../ && mv tools/victus/victus $DEVENV_BIN

#
# Put the $DEVENV_BIN onto the path 
# 

export PATH=$PATH:$DEVENV_BIN
