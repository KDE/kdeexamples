project(projectview)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
                      ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules
)

find_package(KDE4 REQUIRED)
find_package(KDevPlatform REQUIRED)

include_directories(
    ${KDE4_INCLUDES}
    ${KDEVPLATFORM_INCLUDE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}
)

#add_definitions(-DKDE_DEFAULT_DEBUG_AREA=)

set(projectview_SRCS
	projectviewplugin.cpp
)

kde4_add_plugin(kdevprojectviewplugin ${projectview_SRCS})
target_link_libraries(kdevprojectviewplugin ${KDEVPLATFORM_INTERFACES_LIBRARIES} ${KDEVPLATFORM_LANGUAGE_LIBRARIES})

install(TARGETS kdevprojectviewplugin DESTINATION ${PLUGIN_INSTALL_DIR})

install(FILES kdevprojectview.desktop DESTINATION ${SERVICES_INSTALL_DIR})

