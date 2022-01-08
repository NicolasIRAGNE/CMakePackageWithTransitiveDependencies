cmake_minimum_required(VERSION 3.20)

project(LibB LANGUAGES CXX VERSION 1.0)

add_library(LibB STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/LibB.cpp)
add_library(LibB::LibB ALIAS LibB)

add_subdirectory(LibA)

include(FetchContent)

# find_package(nlohmann_json QUIET)
set(JSON_Install ON)
if (NOT nlohmann_json_FOUND)
    message(STATUS "nlohmann_json not found, downloading...")
    FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/nlohmann/json
  GIT_TAG v3.10.5
  GIT_PROGRESS TRUE
  GIT_SHALLOW TRUE
)

    FetchContent_MakeAvailable(json)
endif()

target_link_libraries(LibB PUBLIC nlohmann_json::nlohmann_json)

target_link_libraries(LibB PUBLIC LibA::LibA)

target_include_directories(LibB
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>  # <prefix>/include/mylib
)

set_target_properties(LibB PROPERTIES
    PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/src/LibB.h
)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(CMAKE_CONFIG_DIR "${CMAKE_INSTALL_LIBDIR}/cmake")

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/LibBConfigVersion.cmake" COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "cmake/LibBConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/LibBConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
    PATH_VARS CMAKE_INSTALL_LIBDIR
)

install(TARGETS LibB EXPORT LibBTargets
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
  INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/LibB"
  PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/LibB"
)

install(
  FILES "${CMAKE_CURRENT_BINARY_DIR}/LibBConfigVersion.cmake" "${CMAKE_CURRENT_BINARY_DIR}/LibBConfig.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

install(
    EXPORT LibBTargets
    NAMESPACE LibB::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)