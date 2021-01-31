cmake_minimum_required(VERSION 3.8)

set(This UnitTests)

add_subdirectory(googletest)

file(GLOB SOURCES "*.cpp")

add_executable(${This} ${SOURCES})

target_link_libraries(${This} PUBLIC 
    gtest_main
    chess
)

add_test(
    NAME ${This}
    COMMAND ${This}
)