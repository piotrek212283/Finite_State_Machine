cmake_minimum_required(VERSION 3.15.0)
project(FiniteStateMachine VERSION 0.1.0)
set(CMAKE_BUILD_TYPE Debug)

set(COMPILE_OPTIONS
  -std=c++17
  -Og
  -fdiagnostics-color=always
)



add_executable(${PROJECT_NAME} main.cpp)

target_compile_options(${PROJECT_NAME} PUBLIC ${COMPILE_OPTIONS})

include(CTest)
enable_testing()