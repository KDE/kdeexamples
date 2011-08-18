cmake_minimum_required(VERSION 2.6.2 FATAL_ERROR)

project(kdeexamples)

find_package(KDE4 REQUIRED)

include(KDE4Defaults)

add_definitions(-DQT_USE_FAST_CONCATENATION -DQT_USE_FAST_OPERATOR_PLUS)

install(FILES README DESTINATION ${DATA_INSTALL_DIR}/kdeexamples)

add_subdirectory(attica)
add_subdirectory(authorization)
add_subdirectory(kconfigxt)
add_subdirectory(kcontrolmodules)
add_subdirectory(kdedemo)
add_subdirectory(kdeui)
add_subdirectory(kidletime)
add_subdirectory(knewstuff)
add_subdirectory(kpart)
add_subdirectory(kross)
add_subdirectory(kwallet)
add_subdirectory(kxmlgui)
add_subdirectory(nepomuk)
add_subdirectory(phonon)
add_subdirectory(plasma)
add_subdirectory(solid)
