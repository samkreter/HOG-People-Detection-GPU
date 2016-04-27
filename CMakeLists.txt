cmake_minimum_required(VERSION 2.8)
PROJECT (name)

find_package(OpenCV REQUIRED )

set(CMAKE_CXX_FLAGS "--std=c++11 -Werror")

set( NAME_SRC
    src/hogCpu.cpp
)

#set( NAME_HEADERS
#     include/timing.hpp
#)

find_package(CUDA)
    if(CUDA_FOUND)
    add_executable(CpuGpuHogtest src/CpuGpuHogtest.cpp)
    target_link_libraries(CpuGpuHogtest ${OpenCV_LIBS} )

    add_library(timing src/timing.cpp)
    add_executable(hogGpu src/hogGpu.cpp)
    target_link_libraries(hogGpu ${OpenCV_LIBS} timing)
endif(CUDA_FOUND)


add_executable( run ${NAME_SRC} ${NAME_HEADERS} )
target_link_libraries(run ${OpenCV_LIBS} )
