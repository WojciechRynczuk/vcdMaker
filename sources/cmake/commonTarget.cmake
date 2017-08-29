# commonTarget.cmake
#
# vcdMaker and vcdMerge common build target functions.
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

# Output directory
set(OUTPUT_DIR output)
set(OUTPUT_DIR_ABSOLUE ${CMAKE_CURRENT_BINARY_DIR}/${OUTPUT_DIR})

# Common sources target name.
set(COMMON_LIB_TARGET vcdToolsCommon)
set(PUGIXML_LIB_TARGET pugiXml)

# Function for setting general target properties.
function(add_common_vcdtools_target_props TARGET_NAME)
    # Set C++14 support.
    set_target_properties(${TARGET_NAME} PROPERTIES CXX_STANDARD 14)
    set_target_properties(${TARGET_NAME} PROPERTIES CXX_EXTENSIONS OFF)
    set_target_properties(${TARGET_NAME} PROPERTIES CXX_STANDARD_REQUIRED ON)

    # Set warning flags.
    if (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
        target_compile_options(${TARGET_NAME} PUBLIC -Wall -Wextra -pedantic)
    elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
        target_compile_options(${TARGET_NAME} PUBLIC /W4)
    endif()
endfunction(add_common_vcdtools_target_props)

# Function for target creation.
function(add_vcdtools_target TARGET_NAME TARGET_SOURCES TARGET_HEADERS TARGET_HEADERS_DIR)
    add_executable(${TARGET_NAME} $<TARGET_OBJECTS:${COMMON_LIB_TARGET}> $<TARGET_OBJECTS:${PUGIXML_LIB_TARGET}> ${TARGET_SOURCES} ${COMMON_HEADERS} ${PUGIXML_HEADERS} ${TARGET_HEADERS})

    target_include_directories(${TARGET_NAME} PUBLIC ${COMMON_HEADERS_DIR} ${TARGET_HEADERS_DIR} ${TCLAP_HEADERS_DIR} ${PUGIXML_HEADERS_DIR})

    add_common_vcdtools_target_props(${TARGET_NAME})

    set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
endfunction(add_vcdtools_target)

# Set common sources build

add_library(${COMMON_LIB_TARGET} OBJECT ${COMMON_SOURCES} ${COMMON_HEADERS})
add_library(${PUGIXML_LIB_TARGET} OBJECT ${PUGIXML_SOURCES} ${PUGIXML_HEADERS})

target_include_directories(${COMMON_LIB_TARGET} PUBLIC ${COMMON_HEADERS_DIR} ${TCLAP_HEADERS_DIR} ${PUGIXML_HEADERS_DIR})
target_include_directories(${PUGIXML_LIB_TARGET} PUBLIC ${PUGIXML_HEADERS_DIR})

add_common_vcdtools_target_props(${COMMON_LIB_TARGET})
add_common_vcdtools_target_props(${PUGIXML_LIB_TARGET})
