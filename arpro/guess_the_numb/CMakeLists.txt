cmake_minimum_required(VERSION 3.5)

project(guess_the_numb LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(comp_guesser src/main.cpp)
add_executable(user_guesser src/user_guesser.cpp)
