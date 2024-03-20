cmake_minimum_required(VERSION 3.0)
project(NeuronNetworkFromScratch CXX)

file(GLOB_RECURSE SOURCES src/*.cc)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(NeuronNetworkFromScratch ${SOURCES})
target_compile_options(NeuronNetworkFromScratch PRIVATE -Wall -Wextra -Wpedantic -O3 -flto)
target_link_options(NeuronNetworkFromScratch PRIVATE -flto)
target_include_directories(NeuronNetworkFromScratch PRIVATE include)