set(SRCS main.cpp mainwindow.cpp)

kde4_add_executable(basicaudioplayer ${SRCS})
target_link_libraries(basicaudioplayer ${PHONON_LIBS} ${KDE4_KIO_LIBS})
install(TARGETS basicaudioplayer ${INSTALL_TARGETS_DEFAULT_ARGS})
