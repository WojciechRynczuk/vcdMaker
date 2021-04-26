/// @file common/inc/Version.h
///
/// Version information header.
///
/// @par Full Description
/// Version information header.
///
/// @par Copyright (c) 2018 vcdMaker team
///
/// Permission is hereby granted, free of charge, to any person obtaining a
/// copy of this software and associated documentation files (the "Software"),
/// to deal in the Software without restriction, including without limitation
/// the rights to use, copy, modify, merge, publish, distribute, sublicense,
/// and/or sell copies of the Software, and to permit persons to whom the
/// Software is furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included
/// in all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
/// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
/// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
/// IN THE SOFTWARE.

#pragma once

/// Version component macros.
/// Also used by CMake to get application version.
/// @{
#define D_VERSION_MAJOR 3
#define D_VERSION_MINOR 0
#define D_VERSION_PATCH 2
#define D_RELEASE_NAME  "Nestor"
/// @}

/// Stringification helpers.
/// @{
#define XSTR(s) STR(s)
#define STR(s) #s
/// @}

/// Version string builder.
#define MAKE_VERSION_STR \
    XSTR(D_VERSION_MAJOR) "." XSTR(D_VERSION_MINOR) "." XSTR(D_VERSION_PATCH)

/// Version information namespace.
namespace VERSION
{

    /// Application version components.
    /// @{
    constexpr int MAJOR = D_VERSION_MAJOR;
    constexpr int MINOR = D_VERSION_MINOR;
    constexpr int PATCH = D_VERSION_PATCH;
    /// @}

    /// Application version string.
    constexpr const char *STRING = MAKE_VERSION_STR;

    /// Application release name.
    constexpr const char *RELEASE_NAME = D_RELEASE_NAME;

}

// Now clean up.
#undef MAKE_VERSION_STR
#undef STR
#undef XSTR
#undef D_VERSION_PATCH
#undef D_VERSION_MINOR
#undef D_VERSION_MAJOR
#undef D_RELEASE_NAME
