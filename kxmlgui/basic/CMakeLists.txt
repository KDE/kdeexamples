project(kxmlguibasic)

set(SRCS main.cpp mainwindow.cpp)

kde4_add_executable(kxmlguibasic ${SRCS})
target_link_libraries(kxmlguibasic ${KDE4_KDEUI_LIBS})
install(TARGETS kxmlguibasic ${INSTALL_TARGETS_DEFAULT_ARGS})
