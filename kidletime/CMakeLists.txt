project(kidletime_example)

set(kidletime_example_SRCS main.cpp KIdleTest.cpp)

kde4_add_executable(kidletime_example ${kidletime_example_SRCS})
target_link_libraries(kidletime_example ${KDE4_KUTILS_LIBS})

