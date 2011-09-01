find_package(Nepomuk REQUIRED)

add_definitions(-DDISABLE_NEPOMUK_LEGACY=1)

install(FILES README DESTINATION ${DATA_INSTALL_DIR}/kdeexamples/nepomuk)

add_subdirectory(metadata)
add_subdirectory(ontology)
add_subdirectory(query)
add_subdirectory(service)
