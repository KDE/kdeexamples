# This code is released into the public domain by the author Martin T. Sandsmark

project(KWalletDemo)

find_package(KDE4 REQUIRED)
add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include(KDE4Defaults)
include(MacroLibrary)
include_directories(${KDE4_INCLUDES} ${KDE4_INCLUDE_DIR} ${QT_INCLUDES})

set(SRCS main.cpp dialog.cpp)

kde4_add_executable(kwalletdemo ${SRCS})
target_link_libraries(kwalletdemo ${KDE4_KDECORE_LIBS} ${KDE4_KPARTS_LIBS} ${KDE4_KDEUI_LIBS})
install(TARGETS kwalletdemo ${INSTALL_TARGETS_DEFAULT_ARGS})

