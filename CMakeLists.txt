# MIT License
# 
# Copyright (c) 2022 流陳光
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
cmake_minimum_required(VERSION 3.18)


set( CMAKE_CXX_STANDARD             11              )
set( CMAKE_CXX_STANDARD_REQUIRED    True            )
set( CMAKE_FIND_LIBRARY_PREFIXES    "lib"           )
set( CMAKE_FIND_LIBRARY_SUFFIXES    ".a;.dll.a;.so" )

set ( DEFAULT_CMAKE_INSTALL_PREFIX_PENGU "/srv/http/cgi-bin"   )
set ( DEFAULT_CMAKE_INSTALL_PREFIX_WIN32 "C:/dev/cgi-bin"      )

set ( CMAKE_INSTALL_PREFIX ${DEFAULT_CMAKE_INSTALL_PREFIX_PENGU} CACHE STRING "Where to install" )

if( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
    message( FATAL_ERROR "Binary directory should not be the same as source directory, please specify a different one!" )
endif()


project(despair-cgi VERSION 1.0) ########################################################
add_subdirectory(googletest)


add_library( despair-cgi
    "src/html_document.cc"
    "src/tag.cc"
    )

target_precompile_headers( despair-cgi
    PRIVATE "src/dpcgi_pch.hh"
)

target_include_directories( despair-cgi
    PUBLIC "include"
    )

#########################################################################################

add_executable( runtests
    "tests/basic.cc"
    )

target_include_directories( runtests
    PUBLIC "include"
    PUBLIC "googletest/googletest/include"
)

target_link_libraries( runtests
    PUBLIC despair-cgi gtest gtest_main
)

add_test(NAME runtests COMMAND runtests)

#########################################################################################

add_executable( example
    "examples/despair-cgi.cc"
    )

target_link_libraries( example
    PUBLIC despair-cgi
    )
