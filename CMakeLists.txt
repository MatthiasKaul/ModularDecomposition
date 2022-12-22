cmake_minimum_required(VERSION 3.10)
project(TwinWidth)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()




set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
message (${CMAKE_MODULE_PATH})

set(SOURCE_FILES main.cpp graph.cpp partitionRefinement.cpp)



add_executable(twSolve ${SOURCE_FILES} ${GRB_SOURCE_FILES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
