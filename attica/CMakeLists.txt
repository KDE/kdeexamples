project(Attica)

find_package(LibAttica REQUIRED)

install(FILES README DESTINATION ${DATA_INSTALL_DIR}/kdeexamples/attica)

include(MacroLibrary)
include(MacroOptionalAddSubdirectory)
include_directories(${LIBATTICA_INCLUDE_DIR})

add_subdirectory(opencollaborationexample)
