cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(wei
  VERSION 0.1.0
  LANGUAGES CXX
)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.")
endif()

set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM.cmake")
set(CPM_DOWNLOAD_VERSION 0.25.1)

if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION} AND CPM_VERSION STREQUAL CPM_DOWNLOAD_VERSION))
  message(STATUS "Downloading CPM.cmake")
  file(DOWNLOAD https://github.com/TheLartians/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake ${CPM_DOWNLOAD_LOCATION})
endif()

include(${CPM_DOWNLOAD_LOCATION})

CPMAddPackage(
  NAME fancy
  GITHUB_REPOSITORY KusStar/fancy
  VERSION 0.2.1
)

CPMAddPackage(
  NAME escaper
  GITHUB_REPOSITORY KusStar/escaper
  VERSION 0.1.3
)

# ---- Add source files ----
set(headers "${CMAKE_SOURCE_DIR}/include")
set(sources "${CMAKE_SOURCE_DIR}/source")

include_directories(${headers} ${source})
include_directories(${CMAKE_SOURCE_DIR}/jute)

add_executable(wei ${sources}/main.cpp ${CMAKE_SOURCE_DIR}/jute/jute.cpp)

set_target_properties(wei PROPERTIES
  CXX_STANDARD 11
  OUTPUT_NAME "run"
)

target_link_libraries(wei fancy escaper)
