cmake_minimum_required(VERSION 3.20)

project(LibA LANGUAGES CXX VERSION 1.0)

add_library(LibA STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/LibA.cpp)
add_library(LibA::LibA ALIAS LibA)

target_include_directories(LibA
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>  # <prefix>/include/mylib
)

set_target_properties(LibA PROPERTIES
    PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/src/LibA.h
)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/LibAConfigVersion.cmake" COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "cmake/LibAConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/LibAConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

install(TARGETS LibA EXPORT LibATargets
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
  INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/LibA"
  PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/LibA"
)

install(
  FILES "${CMAKE_CURRENT_BINARY_DIR}/LibAConfigVersion.cmake" "${CMAKE_CURRENT_BINARY_DIR}/LibAConfig.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

install(
    EXPORT LibATargets
    NAMESPACE LibA::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)