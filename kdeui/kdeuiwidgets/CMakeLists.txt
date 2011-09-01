project(kdeuiwidgets)

set(SRCS main.cpp mainwindow.cpp)

kde4_add_executable(kdeuiwidgets ${SRCS})
target_link_libraries(kdeuiwidgets ${KDE4_KDEUI_LIBS})
install(TARGETS kdeuiwidgets ${INSTALL_TARGETS_DEFAULT_ARGS})
install(FILES ${SRCS} mainwindow.h README  DESTINATION ${DATA_INSTALL_DIR}/kdeexamples/kdeui/kdeuiwidgets)
