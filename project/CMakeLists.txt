project(curl_project C CXX)
cmake_minimum_required(VERSION 2.8)

message(STATUS "install dirctory:" ${INSTALL_DIR})

set(CMAKE_FIND_ROOT_PATH ${INSTALL_DIR})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)


find_package(PkgConfig)

#openssl
pkg_check_modules(OPENSSL REQUIRED openssl)
if (OPENSSL_FOUND)
    message(STATUS "openssl library dirctory:" ${OPENSSL_INCLUDE_DIRS})
    message(STATUS "openssl include dirctory:" ${OPENSSL_LIBRARY_DIRS})
    message(STATUS "openssl library:" ${OPENSSL_LIBRARIES})
endif ()

#curl
pkg_check_modules(CURL REQUIRED libcurl)
if (CURL_FOUND)
    message(STATUS "CURL library dirctory:" ${CURL_INCLUDE_DIRS})
    message(STATUS "CURL include dirctory:" ${CURL_LIBRARY_DIRS})
    message(STATUS "CURL library:" ${CURL_LIBRARIES})
endif ()

#define
#add_definitions(-DCURL_HAVE_)

# target include
include_directories(${OPENSSL_INCLUDE_DIRS} ${CURL_INCLUDE_DIRS})
link_directories(${OPENSSL_LIBRARY_DIRS} ${CURL_LIBRARY_DIRS})


#add sub
add_subdirectory(easy_sample)
