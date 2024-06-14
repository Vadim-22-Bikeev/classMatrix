cmake_minimum_required(VERSION 3.20)
project(matrix_operation)

add_compile_options("-mconsole")
include_directories(include)
enable_testing()

add_library(mat STATIC src/mat.cpp)

add_executable(main main.cpp ./src/mat.cpp)

add_executable(mat-test ./tests/mat-test.cpp ./src/mat.cpp)

add_test(NAME mat-test COMMAND mat-test --force-colors -d)

