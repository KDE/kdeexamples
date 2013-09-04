project( tooltipexample )

include_directories (${KDE4_INCLUDES})

set(tooltipexample_SRCS tooltips.cpp)

kde4_add_plugin(plasma_applet_example_tooltips ${tooltipexample_SRCS})
target_link_libraries(plasma_applet_example_tooltips ${KDE4_PLASMA_LIBS})

install(TARGETS plasma_applet_example_tooltips DESTINATION ${PLUGIN_INSTALL_DIR})

install(FILES plasma-applet-example-tooltips.desktop DESTINATION ${SERVICES_INSTALL_DIR})
