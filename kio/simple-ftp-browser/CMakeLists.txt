project(simple-ftp-browser)

include_directories(${KDE4_INCLUDES})

set(SRCS main.cpp browser.cpp)


kde4_add_executable(simple-ftp-browser ${SRCS})
target_link_libraries(simple-ftp-browser ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS})
install(TARGETS simple-ftp-browser ${INSTALL_TARGETS_DEFAULT_ARGS})
install(FILES ${SRCS} browser.h README  DESTINATION ${DATA_INSTALL_DIR}/kdeexamples/kio/simple-ftp-browser)
