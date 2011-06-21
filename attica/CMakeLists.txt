project(Attica)

find_package(LibAttica REQUIRED)

include(MacroLibrary)
include(MacroOptionalAddSubdirectory)

add_subdirectory(example)
