# manPages.cmake
#
# Man page generation.
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

# Set man pages generation.

find_program(TXT2MAN_EXECUTABLE
             NAME txt2man
             PATHS ENV PATH
             DOC "txt2man man pages generation tool")

if (NOT TXT2MAN_EXECUTABLE)
    message(FATAL_ERROR "txt2man executable not found")
endif()

find_program(GZIP_EXECUTABLE
             NAME gzip
             PATHS ENV PATH
             DOC "gzip tool")

if (NOT GZIP_EXECUTABLE)
    message(FATAL_ERROR "gzip executable not found")
endif()

set(MAN_SOURCE_DIR ${PROJECT_SOURCE_DIR}/common/doc/man)
set(MAN_COMMON_OPTIONS -r ${PROJECT_VERSION} -s 1 -v "vcdMaker manual")
set(MAN_PAGES
    vcdMaker
    vcdMerge)

foreach(MAN_PAGE IN LISTS MAN_PAGES)
    add_custom_command(OUTPUT ${OUTPUT_DIR_ABSOLUE}/${MAN_PAGE}.1.gz
                       COMMAND ${TXT2MAN_EXECUTABLE} -t ${MAN_PAGE} ${MAN_COMMON_OPTIONS} ${MAN_SOURCE_DIR}/${MAN_PAGE}.txt > ${MAN_PAGE}.1
                       COMMAND ${GZIP_EXECUTABLE} ${MAN_PAGE}.1
                       WORKING_DIRECTORY ${OUTPUT_DIR_ABSOLUE}
                       VERBATIM)

    list(APPEND MAN_PAGES_GENERATED ${OUTPUT_DIR_ABSOLUE}/${MAN_PAGE}.1.gz)
endforeach(MAN_PAGE)

add_custom_target(manPages
                  ALL
                  DEPENDS ${MAN_PAGES_GENERATED})
