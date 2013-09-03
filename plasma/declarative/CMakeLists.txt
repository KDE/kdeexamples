add_subdirectory(wallpapers)

# # fakemail
# install(DIRECTORY fakemail/ DESTINATION ${DATA_INSTALL_DIR}/plasma/plasmoids/fakemail-qml)
# install(FILES fakemail/metadata.desktop DESTINATION ${SERVICES_INSTALL_DIR} RENAME akemail-example.desktop)
# # nowplaying
# install(DIRECTORY nowplaying/ DESTINATION ${DATA_INSTALL_DIR}/plasma/plasmoids/org.kde.nowplaying-qml)
# install(FILES nowplaying/metadata.desktop DESTINATION ${SERVICES_INSTALL_DIR} RENAME nowplaying-example.desktop)
# # qmltasks
# install(DIRECTORY qmltasks/ DESTINATION ${DATA_INSTALL_DIR}/plasma/plasmoids/qmltasks)
# install(FILES qmltasks/metadata.desktop DESTINATION ${SERVICES_INSTALL_DIR} RENAME qmltasks-example.desktop)
# # samegame
# install(DIRECTORY samegame/ DESTINATION ${DATA_INSTALL_DIR}/plasma/plasmoids/org.kde.samegame-qml)
# install(FILES samegame/metadata.desktop DESTINATION ${SERVICES_INSTALL_DIR} RENAME samegame-example.desktop)

# widgetgallery
plasma_install_package(localegallery org.kde.example.locale)
plasma_install_package(widgetgallery org.kde.example.widgetgallery)
plasma_install_package(qmltasks org.kde.example.tasks)
plasma_install_package(windowlist org.kde.example.windowlist)
plasma_install_package(conditionalloader org.kde.example.conditionalloader)
plasma_install_package(testcomponents org.kde.example.testcomponents)
plasma_install_package(testshaders org.kde.example.testshaders)
plasma_install_package(helloworld org.kde.examples.helloworld)
plasma_install_package(compactrepresentation org.kde.examples.compactrepresentation)
