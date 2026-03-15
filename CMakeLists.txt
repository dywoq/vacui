cmake_minimum_required(VERSION 4.2.3)
project(zero)

file(GLOB_RECURSE SOURCES src/*.c src/**/*.c)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC include/)
target_compile_options(${PROJECT_NAME} PUBLIC --std=c23)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PUBLIC
        DEBUG=1
        RELEASE=0
    )
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(${PROJECT_NAME} PUBLIC
        DEBUG=0
        RELEASE=1
    )
endif()