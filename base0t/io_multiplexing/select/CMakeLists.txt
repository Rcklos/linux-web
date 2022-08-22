cmake_minimum_required(VERSION 3.10)

SET(CMAKE_CXX_COMPILER "g++")
SET(CMAKE_BUILD_TYPE Release)
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

SET(MY_LIB_DIR lib)

project(simple_select)

include_directories(inc ${MY_LIB_DIR}/inc)

aux_source_directory(${MY_LIB_DIR}/src CXX_LIB_SRC)
aux_source_directory(${MY_LIB_DIR}/src/kit CXX_KIT_SRC)
aux_source_directory(src CXX_SRC)

add_executable(main 
  ${CXX_LIB_SRC} 
  ${CXX_KIT_SRC} 
  ${CXX_SRC})
