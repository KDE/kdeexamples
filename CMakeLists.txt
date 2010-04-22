set(plasma_kpart_shell_SRCS
   main.cpp
   containmentshell.cpp
)

kde4_add_executable(plasma-kpart-shell ${plasma_kpart_shell_SRCS})

target_link_libraries(plasma-kpart-shell ${KDE4_KDEUI_LIBS} ${KDE4_KPARTS_LIBS} )

########### install files ###############
install(TARGETS plasma-kpart-shell ${INSTALL_TARGETS_DEFAULT_ARGS} )
install( FILES plasma-kpart-shell.desktop  DESTINATION  ${XDG_APPS_INSTALL_DIR} )
install( FILES plasma-kpart-shell.rc  DESTINATION  ${DATA_INSTALL_DIR}/plasma-kpart-shell )
