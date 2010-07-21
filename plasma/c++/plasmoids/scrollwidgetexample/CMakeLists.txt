project( scrollwidgetexample )

find_package(KDE4 REQUIRED)
include (KDE4Defaults)

include_directories (${KDE4_INCLUDES}
                     ${KDE4WORKSPACE_INCLUDE_DIR}
                     ${KDEPIMLIBS_INCLUDE_DIR}
                     ${CMAKE_CURRENT_SOURCE_DIR}/libs)

set( scrollwidgetexample_SRCS scrollwidgetexample.cpp )

kde4_add_plugin( plasma_applet_scrollwidgetexample ${scrollwidgetexample_SRCS} )
target_link_libraries( plasma_applet_scrollwidgetexample ${KDE4_PLASMA_LIBS} ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS})

install(TARGETS plasma_applet_scrollwidgetexample
        DESTINATION ${PLUGIN_INSTALL_DIR})
 
install(FILES plasma-applet-scrollwidgetexample.desktop
        DESTINATION ${SERVICES_INSTALL_DIR})
