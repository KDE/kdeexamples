project(kdeuiwidgets)

set(SRCS main.cpp mainwindow.cpp)

kde4_add_executable(kdeuiwidgets ${SRCS})
target_link_libraries(kdeuiwidgets ${KDE4_KDEUI_LIBS})
install(TARGETS kdeuiwidgets DESTINATION ${BIN_INSTALL_DIR})
