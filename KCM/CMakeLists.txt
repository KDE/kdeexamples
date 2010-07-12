project( kinfocenterexamples )
find_package( KDE4 REQUIRED )
include_directories( ${KDE4_INCLUDES} )

set( kinfocenterexamplesSources kinfocenter_example.cpp)

kde4_add_plugin( kinfocenterexample ${kinfocenterexamplesSources} )
target_link_libraries( kinfocenterexample ${KDE4_KIO_LIBS} ${KDE4_SOLID_LIBS} )

install( TARGETS kinfocenterexample DESTINATION ${PLUGIN_INSTALL_DIR} )
install( FILES kinfocenterexample.desktop DESTINATION ${SERVICES_INSTALL_DIR} )