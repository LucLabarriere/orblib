cmake_minimum_required(VERSION 3.26)

set(ORBLIB_VERSION 0.1)
message(STATUS "orb::orblib version ${ORBLIB_VERSION}")

project(orblib CXX VERSION ${ORBLIB_VERSION})

add_library(orblib      STATIC src/format.cpp)
add_library(orb::orblib ALIAS  orblib)

if (WIN32)
  target_sources(orblib PRIVATE src/dynlib_windows.cpp
                                src/files_windows.cpp)
else()
  target_sources(orblib PRIVATE src/dynlib_unix.cpp
                                src/files_unix.cpp)
endif()

target_compile_features(orblib    PUBLIC cxx_std_23)
target_include_directories(orblib PUBLIC include)

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


