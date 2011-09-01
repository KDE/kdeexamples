project(krosshello)

include_directories(${KDE4_INCLUDES})

set(krosshello_SRCS main.cpp mainwindow.cpp)
set(SCRIPTS hello.js hello.py hello.rb)

kde4_add_executable(krosshello ${krosshello_SRCS})
target_link_libraries(krosshello ${KDE4_KDEUI_LIBS} ${KDE4_KROSSUI_LIBS})
install(TARGETS krosshello ${INSTALL_TARGETS_DEFAULT_ARGS})
install(FILES ${SCRIPTS} DESTINATION ${DATA_INSTALL_DIR}/kdeexamples/kross/krosshello)
install(FILES ${krosshello_SRCS} mainwindow.h README DESTINATION ${DATA_INSTALL_DIR}/kdeexamples/kross/krosshello)
