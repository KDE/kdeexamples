set(SRCS outputselector.cpp)

automoc4_add_executable(outputselectordemo ${SRCS})
target_link_libraries(outputselectordemo ${PHONON_LIBS} ${KDE4_KIO_LIBS})
install(TARGETS outputselectordemo ${INSTALL_TARGETS_DEFAULT_ARGS})
