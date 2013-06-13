
include_directories( ${KDE4_INCLUDES} ${QT_INCLUDES} )

add_subdirectory(src)

# QML-only thing
install(DIRECTORY package/ DESTINATION ${DATA_INSTALL_DIR}/plasma/packages/org.kde.examples.qmlapp)
install(FILES example-qmlapp.desktop DESTINATION ${XDG_APPS_INSTALL_DIR})

