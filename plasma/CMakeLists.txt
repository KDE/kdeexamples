
include(MacroLibrary)

add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${KDE4_INCLUDES})

add_subdirectory(c++)
add_subdirectory(declarative)
add_subdirectory(javascript)
add_subdirectory(python)
add_subdirectory(ruby)
#add_subdirectory(webkit)
