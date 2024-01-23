cmake_minimum_required(VERSION 3.8)

set(TARGET_NAME The_trivia_game)
add_executable(${TARGET_NAME} main.cpp Game.cpp)
target_include_directories(${TARGET_NAME} PRIVATE .)
target_compile_features(${TARGET_NAME} PRIVATE cxx_std_20)
