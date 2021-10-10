cmake_minimum_required(VERSION 3.15.0)
project(FiniteStateMachine)
set(CMAKE_BUILD_TYPE Debug)

set(COMPILE_OPTIONS
  -std=c++17
  -O0
  -g
  -fdiagnostics-color=always
)

add_executable(${PROJECT_NAME} src/main.cpp)

target_compile_options(${PROJECT_NAME} PUBLIC ${COMPILE_OPTIONS})

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)


## Testing
include(CTest)
enable_testing()
include(GoogleTest)

add_subdirectory(googletest)

add_executable(${PROJECT_NAME}_tests 
  test/finiteStateMachineTests.cpp
)

target_compile_options(${PROJECT_NAME}_tests PUBLIC ${COMPILE_OPTIONS})

target_include_directories(${PROJECT_NAME}_tests PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME}_tests PUBLIC
  gtest
  gtest_main
  gmock
)

gtest_discover_tests(${PROJECT_NAME}_tests)