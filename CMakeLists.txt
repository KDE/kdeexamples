project(kdeexamples)

set(KDE_MIN_VERSION "4.3.60") # for the < 4.2 macro
find_package(KDE4 4.3.60 REQUIRED)
include (KDE4Defaults)
include (MacroLibrary)
include(MacroOptionalDependPackage)

add_definitions (${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${KDE4_INCLUDES})

add_subdirectory(plasma)
add_subdirectory(phonon)
add_subdirectory(solid)

