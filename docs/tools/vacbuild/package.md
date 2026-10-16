# Package

## Introduction

This document provides the package's definition and its configuration file's format and layout.

## What is a package?

In the meaning of `vacbuild`, a package is a module that can be either a program or library.
A package has its own source files, public/private include directories, configuration file
and external package dependencies. Using `vacbuild`, a package can be packed into an archive file (`ZIP`)
that is needed for distribution and building dependencies.
