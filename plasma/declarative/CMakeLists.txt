# addons
install(DIRECTORY addons/ DESTINATION ${DATA_INSTALL_DIR}/plasma/plasmoids/org.kde.addons-example-qml)
install(FILES addons/metadata.desktop DESTINATION ${SERVICES_INSTALL_DIR} RENAME addons-example.desktop)
# fakemail
install(DIRECTORY fakemail/ DESTINATION ${DATA_INSTALL_DIR}/plasma/plasmoids/fakemail-qml)
install(FILES fakemail/metadata.desktop DESTINATION ${SERVICES_INSTALL_DIR} RENAME akemail-example.desktop)
# nowplaying
install(DIRECTORY nowplaying/ DESTINATION ${DATA_INSTALL_DIR}/plasma/plasmoids/org.kde.nowplaying-qml)
install(FILES nowplaying/metadata.desktop DESTINATION ${SERVICES_INSTALL_DIR} RENAME nowplaying-example.desktop)
# qmltasks
install(DIRECTORY qmltasks/ DESTINATION ${DATA_INSTALL_DIR}/plasma/plasmoids/qmltasks)
install(FILES qmltasks/metadata.desktop DESTINATION ${SERVICES_INSTALL_DIR} RENAME qmltasks-example.desktop)
# samegame
install(DIRECTORY samegame/ DESTINATION ${DATA_INSTALL_DIR}/plasma/plasmoids/org.kde.samegame-qml)
install(FILES samegame/metadata.desktop DESTINATION ${SERVICES_INSTALL_DIR} RENAME samegame-example.desktop)
