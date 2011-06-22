find_package(Nepomuk REQUIRED)

add_definitions(-DDISABLE_NEPOMUK_LEGACY=1)

add_subdirectory(metadata)
add_subdirectory(ontology)
add_subdirectory(query)
add_subdirectory(service)
add_subdirectory(test)
