cmake_minimum_required(VERSION 3.22)
project(MainExe LANGUAGES CXX)

# Path to the LibB installation directory
set(LibB_DIR "C:\\Users\\nicor\\Install\\lib\\cmake\\LibB") 
find_package(LibB REQUIRED)

add_executable(MainExe src/main.cpp)
target_link_libraries(MainExe LibB::LibB)
