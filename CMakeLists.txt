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
endif ()

#include top directory
include_directories(include)

#src files
file(GLOB SRC_FILES
        src/*.c
        src/*.cpp
        src/Socket/*.c
        src/Socket/*.cpp
        src/Media/*.c
        src/Media/*.cpp
        src/Util/*.c
        src/Util/*.cpp
        src/Event/*.cpp
        )

#generate shared library
add_library(easyav SHARED ${SRC_FILES})

macro(example module)
    add_executable(${module}Test example/${module}Test.cpp)
    target_link_libraries(${module}Test easyav)
endmacro()

example(Util)
example(TcpServer)
example(RtspServer)