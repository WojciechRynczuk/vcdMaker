# version.cmake
#
# Doxygen target.
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

# Add Doxygen target.

find_package(Doxygen)
set_package_properties(Doxygen PROPERTIES
                       URL "http://doxygen.org"
                       DESCRIPTION "Tool for generating documentation from annotated C++ sources"
                       TYPE OPTIONAL
                       PURPOSE "Enables generation of code documentation.")

if (DOXYGEN_FOUND)
  set(DOXYFILE_IN ${DEVEL_SUPPORT_DIR}/config/Doxyfile.in)
  set(DOXYFILE_OUT Doxyfile.out)

  configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT})

  add_custom_target(doxygen
                    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
                    COMMENT "Generate doxygen documentation"
                    VERBATIM)
endif()
