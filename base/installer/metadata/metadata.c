/*
 * Copyright 2026 dywoq - Apache License 2.0
 * https://github.com/dywoq/vacui
 *
 * An implementation of vqinstmetadata.h
 */

[[nodiscard]]
const char *
MetadataGetTitle()
{
    return "Vacui VQ installer";
}

[[nodiscard]]
const char *
MetadataGetBuildType()
{
#if DEBUG
    return "Debug build";
#elif RELEASE
    return "Release build";
#endif
}

[[nodiscard]]
const char *
MetadataGetVersion()
{
    return "1.0";
}
