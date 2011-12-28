project(kio)

include_directories(${KDE4_INCLUDES})

install(FILES README DESTINATION ${DATA_INSTALL_DIR}/kdeexamples/kio)

add_subdirectory(simple-ftp-browser)
