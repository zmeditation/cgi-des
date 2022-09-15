cmake_minimum_required(VERSION 3.18)


set( CMAKE_CXX_STANDARD             11              )
set( CMAKE_CXX_STANDARD_REQUIRED    True            )
set( CMAKE_FIND_LIBRARY_PREFIXES    "lib"           )
set( CMAKE_FIND_LIBRARY_SUFFIXES    ".a;.dll.a;.so" )

set ( DEFAULT_CMAKE_INSTALL_PREFIX_PENGU "/srv/http/cgi-bin"   )
set ( DEFAULT_CMAKE_INSTALL_PREFIX_WIN32 "C:/dev"       )

set ( CMAKE_INSTALL_PREFIX ${DEFAULT_CMAKE_INSTALL_PREFIX_PENGU} CACHE STRING "Where to install" )

if( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
    message( FATAL_ERROR "Binary directory should not be the same as source directory, please specify a different one!" )
endif()


project(despair-cgi VERSION 1.0)

add_library( despair-cgi
    src/tag.cc
    )

target_include_directories( despair-cgi
    PUBLIC "include"
    )


add_executable( example
    src/despair-cgi.cc
    )

target_link_libraries( example
    PUBLIC despair-cgi
    )
