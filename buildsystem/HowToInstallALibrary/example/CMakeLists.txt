cmake_minimum_required(VERSION 2.6.4)

find_package(Bar 1.2.0 REQUIRED)

include(FindPackageHandleStandardArgs)
#find_package_handle_standard_args(Bar CONFIG_MODE)

include_directories(${BAR_INCLUDES})

add_executable(hello main.c)
target_link_libraries(hello ${BAR_LIBRARIES} )

message(STATUS "version: ${BAR_VERSION}")
