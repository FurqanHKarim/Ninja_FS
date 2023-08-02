cmake_minimum_required(VERSION 3.1)
project(Ninja)
include_directories(${PROJECT_SOURCE_DIR}/include)
add_library(
    STATIC
    ${PROJECT_SOURCE_DIR}/src/
    ${PROJECT_SOURCE_DIR}/src/Data.cpp 
    ${PROJECT_SOURCE_DIR}/src/functions.cpp 
    ${PROJECT_SOURCE_DIR}/src/Access.cpp  
    ${PROJECT_SOURCE_DIR}/src/File_Header.cpp)
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/main.cpp)
