project(tutorial1)

include_directories( ${KDE4_INCLUDE_DIR} ${QT_INCLUDES} )
add_definitions(${QT_DEFINITIONS} ${QDBUS_DEFINITIONS} ${KDE4_DEFINITIONS})

kde4_add_executable(tutorial1 tutorial1.cpp )

target_link_libraries(tutorial1  ${KDE4_KDEUI_LIBS} ${KDE4_SOLID_LIBS} )
