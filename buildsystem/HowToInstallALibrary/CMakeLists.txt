cmake_minimum_required(VERSION 2.8.7)
project(Bar)

# the version number, needed for
# - the library version
# - version detection by cmake
set(BAR_VERSION_MAJOR 1)
set(BAR_VERSION_MINOR 2)
set(BAR_VERSION_PATCH 3)
set(BAR_VERSION ${BAR_VERSION_MAJOR}.${BAR_VERSION_MINOR}.${BAR_VERSION_PATCH} )

# set up install directories. INCLUDE_INSTALL_DIR and LIB_INSTALL_DIR must not be absolute paths
set(LIB_INSTALL_DIR_SUFFIX "" CACHE STRING "The directories where to install libraries to")
set(LIB_INSTALL_DIR lib${LIB_INSTALL_DIR_SUFFIX} )
set(CMAKECONFIG_INSTALL_DIR ${LIB_INSTALL_DIR}/cmake/Bar )

# Use a versioned install directory for the headers so multiple versions can be installed in parallel
set(INCLUDE_INSTALL_DIR include )

# not changable, but we set a variable anyway for consistency
set(BIN_INSTALL_DIR bin)

# actually add the directory where the library is built
add_subdirectory(src)

# This "exports" all targets which have been put into the export set "BarExport".
# This means that cmake generates a file with the given filename, which can later on be loaded
# by projects using this package.
# This file contains add_library(bar IMPORTED) statements for each target in the export set, so
# when loaded later on cmake will create "imported" library targets from these, which can be used
# in many ways in the same way as a normal library target created via a normal add_library().
install(EXPORT BarExport DESTINATION ${CMAKECONFIG_INSTALL_DIR} FILE BarTargets.cmake )

# Create a BarConfig.cmake file. <name>Config.cmake files are searched by find_package()
# automatically. We configure that file so that we can put any information we want in it,
# e.g. version numbers, include directories, etc.
configure_file(BarConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/BarConfig.cmake @ONLY )

# Additionally, when cmake has found a BarConfig.cmake, it can check for a BarConfigVersion.cmake
# in the same directory when figuring out the version of the package when a version
# has been specified in the find_package() call, e.g. find_package(Bar 1.0)
include(WriteBasicConfigVersionFile)
write_basic_config_version_file(${CMAKE_CURRENT_BINARY_DIR}/BarConfigVersion.cmake
                                VERSION ${BAR_VERSION}
                                COMPATIBILITY AnyNewerVersion )

# Install these two files into the same directory as the generated exports-file.
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/BarConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/BarConfigVersion.cmake
        DESTINATION ${CMAKECONFIG_INSTALL_DIR} )


