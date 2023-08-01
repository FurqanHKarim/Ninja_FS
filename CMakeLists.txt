cmake_minimum_required(VERSION 3.1)
project(Ninja)
include_directories(${PROJECT_SOURCE_DIR}/include
)
# add_library(
#     STATIC
#     ${PROJECT_SOURCE_DIR}/src/)
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/main.cpp "src/Data.cpp" "include/functions.h" "src/functions.cpp" "src/Access.cpp")
