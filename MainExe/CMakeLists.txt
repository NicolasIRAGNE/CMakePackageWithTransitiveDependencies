cmake_minimum_required(VERSION 3.22)
project(MainExe LANGUAGES CXX)

# Path to the LibB installation directory
set(LibB_DIR "C:\\Users\\nicor\\Install\\lib\\cmake\\LibB") 
find_package(LibB REQUIRED)

set(CMAKE_VERBOSE_MAKEFILE TRUE)

add_executable(MainExe src/main.cpp)
target_link_libraries(MainExe LibB::LibB)

get_target_property(BLABLA MainExe INTERFACE_INCLUDE_DIRECTORIES)
message(STATUS "BLABLA: ${BLABLA}")
