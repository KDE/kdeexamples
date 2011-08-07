project(kmessagewidgetdemo)

add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include(MacroLibrary)
include_directories(${KDE4_INCLUDES} ${KDE4_INCLUDE_DIR} ${QT_INCLUDES})

set(SRCS main.cpp window.cpp)

kde4_add_executable(kmessagewidgetdemo ${SRCS})
target_link_libraries(kmessagewidgetdemo ${KDE4_KDECORE_LIBS} ${KDE4_KPARTS_LIBS} ${KDE4_KDEUI_LIBS})
install(TARGETS kmessagewidgetdemo ${INSTALL_TARGETS_DEFAULT_ARGS})
