project(nepomukquerydemo)

set(SRCS main.cpp mainwindow.cpp)

include_directories(${KDE4_INCLUDES} ${QT_INCLUDES})
add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})

kde4_add_executable(nepomukquerydemo ${SRCS})
target_link_libraries(nepomukquerydemo ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS} ${NEPOMUK_LIBRARIES})
install(TARGETS nepomukquerydemo DESTINATION ${BIN_INSTALL_DIR})
