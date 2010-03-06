project(Attica)

find_package(KDE4 REQUIRED)
find_package(LibAttica REQUIRED)

include(KDE4Defaults)
include(MacroLibrary)
include(MacroOptionalAddSubdirectory)

add_subdirectory(example)

