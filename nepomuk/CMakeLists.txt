find_package(NepomukCore REQUIRED)
find_package(Soprano REQUIRED)

install(FILES README DESTINATION ${DATA_INSTALL_DIR}/kdeexamples/nepomuk)

add_subdirectory(metadata)
add_subdirectory(ontology)
add_subdirectory(query)
add_subdirectory(service)
add_subdirectory(test)
