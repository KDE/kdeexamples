project(Attica)

find_package(KDE4 REQUIRED)

include(KDE4Defaults)
include(MacroLibrary)
include(MacroOptionalAddSubdirectory)

add_subdirectory(ocs)
add_subdirectory(plasma)

