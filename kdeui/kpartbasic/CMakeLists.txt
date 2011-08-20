project(kpartbasic)

set(SRCS main.cpp mainwindow.cpp)

include_directories(${KDE4_INCLUDES})

kde4_add_executable(kpartbasic ${SRCS})
target_link_libraries(kpartbasic ${KDE4_KDEUI_LIBS} ${KDE4_KPARTS_LIBS})
install(TARGETS kpartbasic  ${INSTALL_TARGETS_DEFAULT_ARGS})
install(FILES ${SRCS} mainwindow.h README DESTINATION ${DATA_INSTALL_DIR}/kdeexamples/kdeui/kpartbasic)
