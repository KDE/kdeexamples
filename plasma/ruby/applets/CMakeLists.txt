# clock
install(DIRECTORY clock/ DESTINATION ${DATA_INSTALL_DIR}/plasma/plasmoids/ruby-clock)
install(FILES clock/metadata.desktop DESTINATION ${SERVICES_INSTALL_DIR} RENAME ruby-clock-example.desktop)
# ruby-extender-tutorial
install(DIRECTORY ruby-extender-tutorial/ DESTINATION ${DATA_INSTALL_DIR}/plasma/plasmoids/ruby-extender-tutorial)
install(FILES ruby-extender-tutorial/metadata.desktop DESTINATION ${SERVICES_INSTALL_DIR} RENAME ruby-extender-tutorial-example.desktop)
# ruby_tiger
install(DIRECTORY ruby_tiger/ DESTINATION ${DATA_INSTALL_DIR}/plasma/plasmoids/ruby-tiger)
install(FILES ruby_tiger/metadata.desktop DESTINATION ${SERVICES_INSTALL_DIR} RENAME ruby-tiger-example.desktop)
# webapplet
install(DIRECTORY webapplet/ DESTINATION ${DATA_INSTALL_DIR}/plasma/plasmoids/ruby-webapplet)
install(FILES webapplet/metadata.desktop DESTINATION ${SERVICES_INSTALL_DIR} RENAME ruby-webapplet-example.desktop)
