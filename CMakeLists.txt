cmake_minimum_required(VERSION 3.10)

project(cppcmake)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# any compiler flags that should be used
#
# 1. `-O3`: enable all optimizations
# 2. `-Wall`: enable all warnings
set(CMAKE_CXX_FLAGS "-O3 -Wall")

# specify the non-header source files that should be compiled
file(GLOB CPP_SOURCE
    "${PROJECT_SOURCE_DIR}/src/*.cpp"   # i.e. `src/main.cpp`, but not `src/d/f.cpp`
    "${PROJECT_SOURCE_DIR}/src/*/*.cpp" # i.e. `src/d/f.cpp`
)

# where to find header files
include_directories(${PROJECT_SOURCE_DIR}/src)

# name of the executable to be created, and which source files to use
add_executable(main ${CPP_SOURCE})

