file(GLOB SRC Event/*.c
              Event/*.cpp
              Media/*.c
              Media/*.cpp
              Socket/*.c
              Socket/*.cpp
              Util/*.c
              Util/*.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(easyav SHARED ${SRC})
target_link_libraries(easyav pthread)