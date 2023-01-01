cmake_minimum_required(VERSION 3.10)
project(ModularDecomp)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)



set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
message (${CMAKE_MODULE_PATH})

set(SOURCE_FILES main.cpp graph.cpp partitionRefinement.cpp modDecomp.cpp)



add_executable(ModularDecomp ${SOURCE_FILES} ${GRB_SOURCE_FILES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
