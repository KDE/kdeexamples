project(minibrowser)

include_directories(${KDE4_INCLUDE_DIR} ${QT_INCLUDES})
add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})

kde4_add_executable(minibrowser main.cpp)

target_link_libraries(minibrowser ${KDE4_KDEUI_LIBS} ${KDE4_SOLID_LIBS})

install(TARGETS minibrowser ${INSTALL_TARGETS_DEFAULT_ARGS})
