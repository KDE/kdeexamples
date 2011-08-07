project(kidletime_example)

add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories(${KDE4_INCLUDES})

set(kidletime_example_SRCS main.cpp KIdleTest.cpp)

kde4_add_executable(kidletime_example ${kidletime_example_SRCS})
target_link_libraries(kidletime_example ${KDE4_KIDLETIME_LIBS})

install(TARGETS kidletime_example ${INSTALL_TARGETS_DEFAULT_ARGS})
