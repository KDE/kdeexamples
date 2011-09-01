# animations
install(DIRECTORY animations/ DESTINATION ${DATA_INSTALL_DIR}/plasma/plasmoids/org.kde.plasma.javascript-animations-example)
install(FILES animations/metadata.desktop DESTINATION ${SERVICES_INSTALL_DIR} RENAME animations-js-example.desktop)
# configuration
install(DIRECTORY configuration/ DESTINATION ${DATA_INSTALL_DIR}/plasma/plasmoids/org.kde.plasma.javascript-config-example)
install(FILES configuration/metadata.desktop DESTINATION ${SERVICES_INSTALL_DIR} RENAME configuration-js-example.desktop)
# digital-clock
install(DIRECTORY digital-clock/ DESTINATION ${DATA_INSTALL_DIR}/plasma/plasmoids/org.kde.plasma.script-digital-clock-example)
install(FILES digital-clock/metadata.desktop DESTINATION ${SERVICES_INSTALL_DIR} RENAME digital-clock-js-example.desktop)
# enumerateAPI
install(DIRECTORY enumerateAPI/ DESTINATION ${DATA_INSTALL_DIR}/plasma/plasmoids/org.kde.plasma.simpified-javascript-enumerator)
install(FILES enumerateAPI/metadata.desktop DESTINATION ${SERVICES_INSTALL_DIR} RENAME enumerate-api-js-example.desktop)
# extenders
install(DIRECTORY extenders/ DESTINATION ${DATA_INSTALL_DIR}/plasma/plasmoids/org.kde.plasma.simpified-javascript-extenders-example)
install(FILES extenders/metadata.desktop DESTINATION ${SERVICES_INSTALL_DIR} RENAME extenders-js-example.desktop)
# geolocation
install(DIRECTORY geolocation/ DESTINATION ${DATA_INSTALL_DIR}/plasma/plasmoids/org.kde.plasma.javascript-geolocation-example)
install(FILES geolocation/metadata.desktop DESTINATION ${SERVICES_INSTALL_DIR} RENAME geolocation-js-example.desktop)
# mediaplayer
install(DIRECTORY mediaplayer/ DESTINATION ${DATA_INSTALL_DIR}/plasma/plasmoids/org.kde.plasma.script-mediaplayer-example)
install(FILES mediaplayer/metadata.desktop DESTINATION ${SERVICES_INSTALL_DIR} RENAME mediaplayer-js-example.desktop)
# notifications
install(DIRECTORY notifications/ DESTINATION ${DATA_INSTALL_DIR}/plasma/plasmoids/org.kde.plasma.script-notifications-example)
install(FILES notifications/metadata.desktop DESTINATION ${SERVICES_INSTALL_DIR} RENAME otifications-js-example.desktop)
# popup
install(DIRECTORY popup/ DESTINATION ${DATA_INSTALL_DIR}/plasma/plasmoids/popupApplet)
install(FILES popup/metadata.desktop DESTINATION ${SERVICES_INSTALL_DIR} RENAME popup-js-example.desktop)
# tiger
install(DIRECTORY tiger/ DESTINATION ${DATA_INSTALL_DIR}/plasma/plasmoids/org.kde.plasma.tiger-example)
install(FILES tiger/metadata.desktop DESTINATION ${SERVICES_INSTALL_DIR} RENAME tiger-js-example.desktop)
# usingServices
install(DIRECTORY usingServices/ DESTINATION ${DATA_INSTALL_DIR}/plasma/plasmoids/org.kde.plasma.script-nowplaying-example)
install(FILES usingServices/metadata.desktop DESTINATION ${SERVICES_INSTALL_DIR} RENAME services-js-example.desktop)
