#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "orb::orblib" for configuration "Release"
set_property(TARGET orb::orblib APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(orb::orblib PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/orblib.lib"
  )

list(APPEND _cmake_import_check_targets orb::orblib )
list(APPEND _cmake_import_check_files_for_orb::orblib "${_IMPORT_PREFIX}/lib/orblib.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
