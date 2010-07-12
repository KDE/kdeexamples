project( kcontrolmoduleexamples )
find_package( KDE4 REQUIRED )
include_directories( ${KDE4_INCLUDES} )

set( kcontrolmoduleSources kcontrolmodule_example.cpp)

kde4_add_plugin( kcontrolmoduleexample ${kcontrolmoduleSources} )
target_link_libraries( kcontrolmoduleexample ${KDE4_KIO_LIBS} ${KDE4_SOLID_LIBS} )

install( TARGETS kcontrolmoduleexample DESTINATION ${PLUGIN_INSTALL_DIR} )
install( FILES kinfocenterexample.desktop DESTINATION ${SERVICES_INSTALL_DIR} )
install( FILES systemsettingsexample.desktop DESTINATION ${SERVICES_INSTALL_DIR} )
