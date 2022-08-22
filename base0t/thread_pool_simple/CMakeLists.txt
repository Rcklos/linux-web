cmake_minimum_required(VERSION 3.10)

SET(CMAKE_CXX_COMPILER "g++")
SET(CMAKE_BUILD_TYPE Release)
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -lpthread")
# SET(THREADS_PREFER_PTHREAD_FLAG ON)

project(thread_pool)

# find_package(Threads)
include_directories(inc)

aux_source_directory(src CXX_SRC)

add_executable(main ${CXX_SRC})
# TARGET_LINK_LIBRARIES(main pthread)
# TARGET_LINK_LIBRARIES(main ${CMAKE_THREAD_LIBS_INIT})
