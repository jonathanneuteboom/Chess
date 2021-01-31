cmake_minimum_required(VERSION 3.8)

set(This chess)

project(${This} CXX)

set(CMAKE_CXX_STANDARD 11)

enable_testing()

include_directories(${This} include)
include_directories(${This} src)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")

add_library(${This} STATIC ${SOURCES} ${Headers})

add_subdirectory(tests)