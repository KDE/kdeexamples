project(kdeui)

find_package(KDE4 REQUIRED)
include_directories(${KDE4_INCLUDES})

add_subdirectory(widgets)
