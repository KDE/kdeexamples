project(sonnet-dialog)

set(SRCS main.cpp mainwindow.cpp)

kde4_add_executable(sonnet-dialog ${SRCS})
target_link_libraries(sonnet-dialog ${KDE4_KDEUI_LIBS})
install(TARGETS sonnet-dialog ${INSTALL_TARGETS_DEFAULT_ARGS})
install(FILES ${SRCS} mainwindow.h README  DESTINATION ${DATA_INSTALL_DIR}/kdeexamples/sonnet/sonnet-dialog)
