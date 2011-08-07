project(tutorial2)

include_directories( ${KDE4_INCLUDE_DIR} ${QT_INCLUDES} )
add_definitions(${QT_DEFINITIONS} ${QDBUS_DEFINITIONS} ${KDE4_DEFINITIONS})

set(tutorial2_SRCS tutorial2.cpp )

kde4_add_executable(tutorial2 ${tutorial2_SRCS})

target_link_libraries(tutorial2  ${KDE4_KDEUI_LIBS} ${KDE4_SOLID_LIBS} )
