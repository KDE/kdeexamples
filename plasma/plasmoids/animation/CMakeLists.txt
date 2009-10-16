# Project Needs a name, of course
project(plasmaanimationexample)

# We add our source code here
set(example_SRCS PlasmaAnimationExample.cpp)

# Now make sure all files get to the right place
kde4_add_plugin(plasma_applet_example_animation ${example_SRCS})
target_link_libraries(plasma_applet_example_animation ${KDE4_PLASMA_LIBS})

# Install the library and .desktop file
install(TARGETS plasma_applet_example_animation DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES plasma-applet-example-animation.desktop DESTINATION ${SERVICES_INSTALL_DIR})
