# addons
install(DIRECTORY addons/ DESTINATION ${DATA_INSTALL_DIR}/plasma/plasmoids/org.kde.addons-example-qml)
install(FILES addons/addons-example.desktop DESTINATION ${SERVICES_INSTALL_DIR})
# digital clock
install(DIRECTORY digital-clock/ DESTINATION ${DATA_INSTALL_DIR}/plasma/plasmoids/org.kde.digital-clock-qml)
install(FILES digital-clock/digital-clock-example.desktop DESTINATION ${SERVICES_INSTALL_DIR})
# fakemail
install(DIRECTORY fakemail/ DESTINATION ${DATA_INSTALL_DIR}/plasma/plasmoids/fakemail-qml)
install(FILES fakemail/fakemail-example.desktop DESTINATION ${SERVICES_INSTALL_DIR})
# nowplaying
install(DIRECTORY nowplaying/ DESTINATION ${DATA_INSTALL_DIR}/plasma/plasmoids/org.kde.nowplaying-qml)
install(FILES nowplaying/nowplaying-example.desktop DESTINATION ${SERVICES_INSTALL_DIR})
# qmltasks
install(DIRECTORY qmltasks/ DESTINATION ${DATA_INSTALL_DIR}/plasma/plasmoids/qmltasks)
install(FILES qmltasks/qmltasks-example.desktop DESTINATION ${SERVICES_INSTALL_DIR})
# samegame
install(DIRECTORY samegame/ DESTINATION ${DATA_INSTALL_DIR}/plasma/plasmoids/org.kde.samegame-qml)
install(FILES samegame/samegame-example.desktop DESTINATION ${SERVICES_INSTALL_DIR})
