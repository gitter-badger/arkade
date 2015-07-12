cmake_minimum_required(VERSION 3.0)

project(arkade)

set(CMAKE_C_FLAGS "-Wall -Wextra -Wno-unused-parameter -std=c99")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")

include_directories(includes includes/toml)

file(GLOB SOURCES src/*.c src/toml/*.c)
file(GLOB HEADERS includes/*.h includes/toml/*.h)

add_executable(arkade ${SOURCES} ${HEADERS})

target_link_libraries(arkade curl)