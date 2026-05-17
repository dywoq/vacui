/*
 * Copyright 2026 dywoq - Apache License 2.0
 * https://github.com/dywoq/vacui
 *
 * An implementation of vqinstmetadata.h
 */

#ifndef _VQINSTMETADATA_H
#define _VQINSTMETADATA_H

[[nodiscard]]
const char *
MetadataGetTitle();

[[nodiscard]]
const char *
MetadataGetBuildType();

[[nodiscard]]
const char *
MetadataGetVersion();

#endif
