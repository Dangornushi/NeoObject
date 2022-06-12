cmake_minimum_required(VERSION 3.23.1)
project(neObj CXX)
add_executable(neObj main.cpp Lexer.cpp Parser.cpp)
set_property(TARGET neObj PROPERTY CXX_STANDARD 20)                       
