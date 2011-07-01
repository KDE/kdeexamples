project(kdeui)

include_directories(${KDE4_INCLUDES})

install(FILES README DESTINATION ${DATA_INSTALL_DIR}/kdeexamples/kdeui)

add_subdirectory(kmessagewidget)
add_subdirectory(widgets)
