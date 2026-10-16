# Package

## Introduction

This document provides the package's definition and its configuration file's format and layout.

## What is a package?

In the meaning of `vacbuild`, a package is a module that can be either a program or library.
A package has its own source files, public/private include directories, configuration file
and external package dependencies. Using `vacbuild`, a package can be packed into an archive
file (`ZIP`) that is needed for distribution and building dependencies.

## Configuration

The package's configuration file relies on the [**TOML v1.1.0**](https://toml.io/en/v1.1.0) format.
Since a package can be either a program or library, the configuration file defines two sections that consist of
type-dependent information: `package.program` and `package.library`.

Subsequent chapters provide a description of sections and their keys.

### Invariants

- All configuration keys that specify physical filepath shall be relative to the package's directory.

### `general`

This section consists of the package's general information that does not depend on the package's type.

| **Key**             | **Type** | **Description**                                                        |
| ------------------- | -------- | ---------------------------------------------------------------------- |
| `type`              | `string` | Defines the package's type. **Allowed options**: `program`, `library`. |
| `default_toolchain` | `string` | Specifies the default toolchain's path.                                |
| `output_file`       | `string` | Specifies the final output's path.                                     |
