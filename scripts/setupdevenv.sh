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
#           source scripts/setupdevenv.
#

#
# Create the .devenv/bin directory
# 

export DEVENV_BIN=$(pwd)/.devenv/bin
mkdir $DEVENV_BIN -p

#
# Compile the host OS development tools
# 

# Victus
echo "Compiling Victus..."
cd tools/victus && go build . && cd ../../ && mv tools/victus/victus $DEVENV_BIN

#
# Put the $DEVENV_BIN onto the path 
# 

echo "Setting up the PATH variable..."
export PATH=$PATH:$DEVENV_BIN

#
# Define environment variables
# 

echo "Defining environment variables..."
export VACUI_BASE=$(pwd)/base
export VACUI_TEMPLATES=$(pwd)/templates
export VACUI_TOOLCHAINS=$(pwd)/toolchains

#
# Final message
# 

echo "The development environment is done! :> Now, you can run commands,"
echo "compiled directly from the source tree:"
echo ""
echo "      [dywoq@ArchLinux vacui] victus"
echo "      C/C++ Build orchestrator, which is specifically made for Vacui"
echo "      ..."
echo ""
echo "The defined environment variables":
echo ""
echo "      VACUI_BASE          $VACUI_BASE"
echo "      VACUI_TEMPLATES     $VACUI_TEMPLATES"
echo "      VACUI_TOOLCHAINS    $VACUI_TOOLCHAINS"
echo ""
