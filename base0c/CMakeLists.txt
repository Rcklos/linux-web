cmake_minimum_required(VERSION 3.20)

project(myDemo)

include_directories(include_dir)

add_executable(myDemo demo.cpp)
add_executable(rallDemo rall_demo.cpp)
add_executable(bind_demo bind_demo.cpp)
