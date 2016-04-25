cmake_minimum_required(VERSION 2.8)
PROJECT (name)

find_package(OpenCV REQUIRED )

set(CMAKE_CXX_FLAGS "--std=c++11 -Werror")

set( NAME_SRC
    src/test.cpp
)

#set( NAME_HEADERS
#     include/header.h
#)

#INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/include )
#link_directories( ${CMAKE_BINARY_DIR}/bin)
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
add_executable( run ${NAME_SRC} ${NAME_HEADERS} )

target_link_libraries( run ${OpenCV_LIBS} )
