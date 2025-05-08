cmake_minimum_required(VERSION 3.22)

set(ORBLIB_VERSION 0.1)
message(STATUS "orb::orblib version ${ORBLIB_VERSION}")

project(orblib
  LANGUAGES CXX
  VERSION   ${ORBLIB_VERSION})

add_library(orblib      STATIC src/format.cpp)
add_library(orb::orblib ALIAS  orblib)

if (WIN32)
  target_sources(orblib PRIVATE src/dynlib_windows.cpp
                                src/files_windows.cpp)
else()
  target_sources(orblib PRIVATE src/dynlib_unix.cpp
                                src/files_unix.cpp)

  target_compile_options(orblib PRIVATE -fPIC)
endif()

target_compile_features(orblib
  PUBLIC cxx_std_23)

target_include_directories(orblib
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:include>)

if (${ORB_ASSERT})
  target_compile_definitions(orblib PUBLIC ORB_ASSERT)
else()
  target_compile_definitions(orblib
    PUBLIC $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:ORB_ASSERT>)
endif()

option(ORBLIB_BUILD_SAMPLES "Build samples of the orb::orblib library" ON)
message(STATUS ${ORB_COMPILER})

if (${ORBLIB_BUILD_SAMPLES})
  message(STATUS "Building orb::orblib samples")
  add_subdirectory(samples)
endif()

# Installation and export
include(CMakePackageConfigHelpers)

# Installation directories
set(INSTALL_CONFIGDIR lib/cmake/orblib)

# Install targets
install(
  TARGETS  orblib
  EXPORT   orblibTargets
  ARCHIVE  DESTINATION lib
  LIBRARY  DESTINATION lib
  RUNTIME  DESTINATION bin
  INCLUDES DESTINATION include)

# Install headers
install(
  DIRECTORY   include/
  DESTINATION include)

# Export target configuration
install(
  EXPORT    orblibTargets
  FILE      orblibTargets.cmake
  NAMESPACE orb::

  DESTINATION ${INSTALL_CONFIGDIR})

# Create a version file
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/orblibConfigVersion.cmake
  VERSION       ${ORBLIB_VERSION}
  COMPATIBILITY SameMajorVersion)

# Create a config file
configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/orblibConfig.cmake

  INSTALL_DESTINATION ${INSTALL_CONFIGDIR})

# Install config files
install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/orblibConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/orblibConfigVersion.cmake

  DESTINATION ${INSTALL_CONFIGDIR})
