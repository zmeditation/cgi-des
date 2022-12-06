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
if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wconversion -pedantic -Werror)
endif()


set( CMAKE_CXX_STANDARD             17              )
set( CMAKE_CXX_STANDARD_REQUIRED    True            )
set( CMAKE_FIND_LIBRARY_PREFIXES    "lib"           )
set( CMAKE_FIND_LIBRARY_SUFFIXES    ".a;.dll.a;.so" )

set ( DEFAULT_CMAKE_INSTALL_PREFIX_PENGU "/srv/http/cgi-bin"   )
set ( DEFAULT_CMAKE_INSTALL_PREFIX_WIN32 "C:/dev/cgi-bin"      )

set ( CMAKE_INSTALL_PREFIX ${DEFAULT_CMAKE_INSTALL_PREFIX_PENGU} CACHE STRING "Where to install" )

if( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
    message( FATAL_ERROR "Binary directory should not be the same as source directory, please specify a different one!" )
endif()


set( DPCGI_SHARED_LIB False CACHE BOOL "Build as shared/DLL library")
set(BUILD_GMOCK False CACHE BOOL "Builds the googlemock subproject")
set( DPCGI_SHARED_LIB_SPEC "STATIC" )

if( ${DPCGI_SHARED_LIB} )
    set( DPCGI_SHARED_LIB_SPEC "SHARED" )
endif()

function(group_target)
    set_target_properties( ${ARGV0} PROPERTIES FOLDER ${ARGV1} )
endfunction()


project(despair-cgi VERSION 1.0) ########################################################
set_property(GLOBAL PROPERTY USE_FOLDERS TRUE)


message( CHECK_START "Configure Google Test" )
add_subdirectory(googletest)
group_target( gtest "gtest" )
group_target( gtest_main "gtest" )
if(BUILD_GMOCK)
    group_target( gmock "gtest" )
    group_target( gmock_main "gtest" )
endif()
message( CHECK_PASS "Done." )

add_library( despair-cgi ${DPCGI_SHARED_LIB_SPEC}
    "src/cookie.cc"
    "src/form.cc"
    "src/html_document.cc"
    "src/query_string.cc"
    "src/tag.cc"
)
if( ${DPCGI_SHARED_LIB} )
    target_compile_definitions(despair-cgi PUBLIC DPCGI_EXPORT)
endif()
target_precompile_headers( despair-cgi
    PRIVATE "src/dpcgi_pch.hh"
)
target_include_directories( despair-cgi
    PUBLIC "include/dpcgi"
)

#########################################################################################

add_executable( runtests
    "tests/cookie.cc"
    "tests/html_document.cc"
    "tests/query_string.cc"
    "tests/tag.cc"
)
target_include_directories( runtests
    PUBLIC "include"
    PUBLIC "googletest/googletest/include"
)
target_link_libraries( runtests
    PUBLIC despair-cgi gtest gtest_main
)
target_precompile_headers( runtests
    PRIVATE tests/tests_pch.hh
)

add_test(NAME runtests COMMAND runtests)

#########################################################################################

function(dpcgi_add_example)
    add_executable( ${ARGV0}
        "examples/eg-${ARGV0}.cc"
    )
    if( DPCGI_SHARED_LIB )
        target_compile_definitions( ${ARGV0} PUBLIC DPCGI_IMPORT )
    endif()
    target_link_libraries( ${ARGV0}
        PUBLIC despair-cgi
    )
    group_target( ${ARGV0} "exe_examples" )
endfunction()

dpcgi_add_example(form)
dpcgi_add_example(html_document)
dpcgi_add_example(query_string)
dpcgi_add_example(tag)
