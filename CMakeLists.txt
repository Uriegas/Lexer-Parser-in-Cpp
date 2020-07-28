#Simple CMakeLists.txt, it is just a template
cmake_minimum_required(VERSION 3.2)

project(cpp_code_test)

#if want to include libraries decomment this
#include_dir()
#add_library()

##Debuging Symbols and Optimization Activated
set(CMAKE_BUILD_TYPE RelWithDebInfo)
 
##Uncomment for Realese Mode and Comment above macro
##set(CMAKE_BUILD_TYPE Release)

#building project
add_executable(cpp_code_test src/main.cpp)
