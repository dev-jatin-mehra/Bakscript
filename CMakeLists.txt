cmake_minimum_required(VERSION 3.10)
project(BakScript)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(BakScript src/main.c src/lexer.c)