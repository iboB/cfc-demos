cmake_minimum_required(VERSION 3.2)

project(cfc-demo)

set(CMAKE_CXX_STANDARD 11)

# picobench
set(picobench_dir ${CMAKE_CURRENT_SOURCE_DIR}/picobench)
add_library(picobench
    picobench/picobench.hpp
    # this header is not part of the library but is used in a common lib to make
    # the compilation of the executables faster
    picobench/picobench.cpp
)

macro(add_exe name src)
    add_executable(${name} ${src})
    target_link_libraries(${name} picobench)
endmacro()

# benchmarks
add_exe(demo1 demo1.cpp)
add_exe(demo2 demo2.cpp)
add_exe(demo3 demo3.cpp)
add_exe(demo4 demo4.cpp)
add_exe(demo5 demo5.cpp)
add_exe(demo6 demo6.cpp)
