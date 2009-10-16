# Auth example application
project(kauthorization_example)

set(KDE_MIN_VERSION "4.3.60") # for the < 4.2 macro
find_package(KDE4 4.3.60 REQUIRED)
include (KDE4Defaults)
include (MacroLibrary)
include(MacroOptionalDependPackage)

add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${KDE4_INCLUDES})


set( kauth_example_sources
     main.cpp
     mainwindow.cpp )

qt4_wrap_ui(kauth_example_uis mainwindow.ui)

kde4_add_executable(kauth_example ${kauth_example_sources} ${kauth_example_uis})
target_link_libraries(kauth_example ${KDE4_KFILE_LIBS})

# Auth example helper
set(kauth_example_helper_srcs helper/helper.cpp)
kde4_add_executable(kauth_example_helper ${kauth_example_helper_srcs})
target_link_libraries(kauth_example_helper ${KDE4_KDECORE_LIBS})
install(TARGETS kauth_example_helper DESTINATION ${LIBEXEC_INSTALL_DIR})

kde4_install_auth_helper_files(kauth_example_helper org.kde.auth.example root)
kde4_install_auth_actions(org.kde.auth.example actions.actions)

# miscellaneous
set_target_properties(kauth_example PROPERTIES COMPILE_FLAGS "-Wall -ggdb")
set_target_properties(kauth_example_helper PROPERTIES COMPILE_FLAGS "-Wall -ggdb")
