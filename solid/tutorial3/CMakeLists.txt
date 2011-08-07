project(tutorial3)

include_directories( ${KDE4_INCLUDE_DIR} ${QT_INCLUDES} )
add_definitions(${QT_DEFINITIONS} ${QDBUS_DEFINITIONS} ${KDE4_DEFINITIONS})

set(tutorial3_SRCS tutorial3.cpp )

kde4_add_executable(tutorial3 ${tutorial3_SRCS})

target_link_libraries(tutorial3  ${KDE4_KDEUI_LIBS} ${KDE4_SOLID_LIBS} )
