project(kconfigxt_example)

set(kconfigxt_example_SRCS example.cpp)
kde4_add_kcfg_files(kconfigxt_example_SRCS exampleprefs_base.kcfgc)

kde4_add_executable(kconfigxt_example ${kconfigxt_example_SRCS})
target_link_libraries(kconfigxt_example ${KDE4_KDEUI_LIBS})

