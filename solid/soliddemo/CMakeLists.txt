project(soliddemo)

set(SRCS main.cpp mainwindow.cpp)

include_directories(${KDE4_INCLUDES} ${QT_INCLUDES})
add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})

kde4_add_executable(soliddemo ${SRCS})
target_link_libraries(soliddemo ${KDE4_KDEUI_LIBS} ${KDE4_SOLID_LIBS})
install(TARGETS soliddemo ${INSTALL_TARGETS_DEFAULT_ARGS})
