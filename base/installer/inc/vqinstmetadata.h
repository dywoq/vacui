/*
 * Copyright 2026 dywoq - Apache License 2.0
 * https://github.com/dywoq/vacui
 *
 * This header contains the functions to get the installer's metadata
 * in strings.
 */

#ifndef _VQINSTMETADATA_H
#define _VQINSTMETADATA_H

/*
 * Provides  the installer title in string.
 */
[[nodiscard]]
const char *
MetadataGetTitle();

/*
 * Provides the build type in string. Return values:
 * - If macro RELEASE is defined -> "Release build"
 * - If macro DEBUG is defined -> "Debug build"
 */
[[nodiscard]]
const char *
MetadataGetBuildType();

/*
 * Provides the installer version in string.
 */
[[nodiscard]]
const char *
MetadataGetVersion();

#endif
