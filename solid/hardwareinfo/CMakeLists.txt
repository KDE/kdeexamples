project(hardwareinfo)

set(SRCS main.cpp mainwindow.cpp)

# search KDE4 and use apply default (but optional) settings
find_package(KDE4 REQUIRED)
include(KDE4Defaults)

include_directories(${KDE4_INCLUDES} ${QT_INCLUDES})
add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})

kde4_add_executable(hardwareinfo ${SRCS})
target_link_libraries(hardwareinfo ${KDE4_KDEUI_LIBS} ${KDE4_SOLID_LIBS})
install(TARGETS hardwareinfo DESTINATION ${BIN_INSTALL_DIR})
