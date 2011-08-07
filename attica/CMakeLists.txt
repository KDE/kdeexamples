project(Attica)

find_package(LibAttica REQUIRED)

include(MacroLibrary)
include(MacroOptionalAddSubdirectory)
include_directories(${LIBATTICA_INCLUDE_DIR})

add_subdirectory(example)
