# installCpack.cmake
#
# CPack settings.
#
# Copyright (c) 2017 vcdMaker team
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.

# Set Cpack.

set(AUTHOR "vcdMaker team")
set(WEBSITE "http://vcdmaker.org")
set(DESCRIPTION "Commandline tools that can generate VCD files from text logs")

set(CPACK_PACKAGE_VENDOR ${AUTHOR})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Generates VCD files from text logs")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_DIRECTORY ${OUTPUT_DIR_ABSOLUE})
set(CPACK_STRIP_FILES ON)
set(CPACK_GENERATOR "RPM" "DEB" "ZIP")

set(CPACK_SYSTEM_NAME ${CMAKE_SYSTEM_PROCESSOR})
if (CPACK_SYSTEM_NAME STREQUAL "x86_64")
    set(CPACK_SYSTEM_NAME "amd64")
endif()

set(CPACK_RPM_PACKAGE_RELEASE 1)
set(CPACK_RPM_PACKAGE_LICENSE "MIT")
set(CPACK_RPM_PACKAGE_URL ${WEBSITE})
set(CPACK_RPM_PACKAGE_DESCRIPTION ${DESCRIPTION})

set(CPACK_DEBIAN_PACKAGE_RELEASE 1)
set(CPACK_DEBIAN_PACKAGE_MAINTAINER ${AUTHOR})
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION ${DESCRIPTION})
set(CPACK_DEBIAN_PACKAGE_SECTION "electronics")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE ${WEBSITE})

include(CPack)
