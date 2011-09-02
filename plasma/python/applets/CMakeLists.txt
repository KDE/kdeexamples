# pyclock
install(DIRECTORY pyclock/ DESTINATION ${DATA_INSTALL_DIR}/plasma/plasmoids/plasma-pyclock)
install(FILES pyclock/metadata.desktop DESTINATION ${SERVICES_INSTALL_DIR} RENAME pyclock-example.desktop)
# pyhello
install(DIRECTORY pyhello/ DESTINATION ${DATA_INSTALL_DIR}/plasma/plasmoids/pyhello)
install(FILES pyhello/metadata.desktop DESTINATION ${SERVICES_INSTALL_DIR} RENAME pyhello-example.desktop)
