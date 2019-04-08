# pugixml.cmake
#
# Pugixml library support.
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

option(USE_STATIC_PUGIXML "Set to ON to build and static link pugixml library, set to OFF to use system library." OFF)
add_feature_info(StaticPugixml USE_STATIC_PUGIXML "Enables usage of source based, bundled pugixml library.")

if (USE_STATIC_PUGIXML)
    set(PUGIXML_OUTPUT_DIR ${OUTPUT_DIR_ABSOLUE}/pugixml)
    set(PUGIXML_INSTALL_DIR ${PUGIXML_OUTPUT_DIR}/install)

    include(ExternalProject)
    ExternalProject_Add(pugixml_project
                        SOURCE_DIR ${PROJECT_SOURCE_DIR}/3rdParty/pugixml
                        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${PUGIXML_INSTALL_DIR} -DCMAKE_BUILD_TYPE=Release
                        BUILD_IN_SOURCE OFF
                        BINARY_DIR ${PUGIXML_OUTPUT_DIR}
                        INSTALL_DIR ${PUGIXML_INSTALL_DIR}
                        TMP_DIR ${PUGIXML_OUTPUT_DIR}/tmp
                        STAMP_DIR ${PUGIXML_OUTPUT_DIR}/stamp)

    add_dependencies(vcdMaker pugixml_project)
    add_dependencies(vcdMerge pugixml_project)

    add_library(pugixml STATIC IMPORTED)

    if(WIN32)
        set(LIB_PREFIX "")
        set(LIB_SUFFIX ".lib")
    else()
        set(LIB_PREFIX "lib")
        set(LIB_SUFFIX ".a")
    endif()

    set(PUGIXML_LIB_FILE ${PUGIXML_OUTPUT_DIR}/${LIB_PREFIX}pugixml${LIB_SUFFIX})

    set(PUGIXML_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/3rdParty/pugixml/src)

    set_target_properties(pugixml PROPERTIES
                          IMPORTED_LOCATION ${PUGIXML_LIB_FILE}
                          INTERFACE_INCLUDE_DIRECTORIES ${PUGIXML_INCLUDE_DIR})

    target_include_directories(${COMMON_LIB_TARGET} PUBLIC ${PUGIXML_INCLUDE_DIR})

    list(APPEND MAKE_CLEAN_FILES ${PUGIXML_LIB_FILE})
else()
    find_package(pugixml REQUIRED)
    set_package_properties(pugixml PROPERTIES
                           URL "http://pugixml.org"
                           DESCRIPTION "Light-weight C++ XML processing library."
                           TYPE REQUIRED
                           PURPOSE "Enables parsing of XML files.")
endif()

target_link_libraries(vcdMaker pugixml)
target_link_libraries(vcdMerge pugixml)
