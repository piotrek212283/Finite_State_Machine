cmake_minimum_required(VERSION 3.15.0)
project(FiniteStateMachine VERSION 0.1.0)
set(CMAKE_BUILD_TYPE Debug)

set(COMPILE_OPTIONS
  -std=c++17
  -Og
  -fdiagnostics-color=always
)


add_executable(${PROJECT_NAME} src/main.cpp)

target_compile_options(${PROJECT_NAME} PUBLIC ${COMPILE_OPTIONS})

target_include_directories(${PROJECT_NAME} PUBLIC

  ${CMAKE_CURRENT_SOURCE_DIR}

)

include(CTest)
enable_testing()

#include(GoogleTest)
#gtest_discover_tests()