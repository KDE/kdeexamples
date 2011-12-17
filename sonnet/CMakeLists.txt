project(sonnet-examples)

include_directories(${KDE4_INCLUDES})

install(FILES README DESTINATION ${DATA_INSTALL_DIR}/kdeexamples/sonnet)

add_subdirectory(dialog)
