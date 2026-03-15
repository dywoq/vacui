cmake_minimum_required(VERSION 4.2.3)
project(zero)

file(GLOB_RECURSE SOURCES src/*.c src/**/*.c)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC include/)
target_compile_options(${PROJECT_NAME} PUBLIC --std=c23)
