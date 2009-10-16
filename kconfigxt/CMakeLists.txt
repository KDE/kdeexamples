project(kconfigxt_example)

set(KDE_MIN_VERSION "4.3.60") # for the < 4.2 macro
find_package(KDE4 4.3.60 REQUIRED)
include (KDE4Defaults)
include (MacroLibrary)
include(MacroOptionalDependPackage)

add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${KDE4_INCLUDES})

set(kconfigxt_example_SRCS example.cpp)
kde4_add_kcfg_files(kconfigxt_example_SRCS exampleprefs_base.kcfgc)

kde4_add_executable(kconfigxt_example ${kconfigxt_example_SRCS})
target_link_libraries(kconfigxt_example ${KDE4_KDEUI_LIBS})

