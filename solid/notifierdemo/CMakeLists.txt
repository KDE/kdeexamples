project(solidnotifierdemo)

set(SRCS main.cpp mainwindow.cpp)

include_directories(${KDE4_INCLUDES} ${QT_INCLUDES})
add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})

kde4_add_executable(solidnotifierdemo ${SRCS})
target_link_libraries(solidnotifierdemo ${KDE4_KDEUI_LIBS} ${KDE4_SOLID_LIBS})
install(TARGETS solidnotifierdemo DESTINATION ${BIN_INSTALL_DIR})
