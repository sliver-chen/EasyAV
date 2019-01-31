cmake_minimum_required(VERSION 2.8)

project(EasyAV)

#environment setting
set(CMAKE_MACOSX_RPATH 0)

#set c/c++ standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

#definitions
if (CMAKE_BUILD_TYPE STREQUAL Debug)
    add_definitions(-DDEBUG)
    set(CMAKE_CXX_FLAGS "-g")
endif ()

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(demo)