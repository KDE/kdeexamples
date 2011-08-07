project(kconfigxt_example)

include(MacroLibrary)

add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories(${KDE4_INCLUDES})

set(kconfigxt_example_SRCS example.cpp)
kde4_add_kcfg_files(kconfigxt_example_SRCS exampleprefs_base.kcfgc)

kde4_add_executable(kconfigxt_example ${kconfigxt_example_SRCS})
target_link_libraries(kconfigxt_example ${KDE4_KDEUI_LIBS})

install(TARGETS kconfigxt_example ${INSTALL_TARGETS_DEFAULT_ARGS})
