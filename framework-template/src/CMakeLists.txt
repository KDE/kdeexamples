set(foobar_SRCS
  myclass.cpp
)

add_library(KF5FooBar ${foobar_SRCS})
generate_export_header(KF5FooBar BASE_NAME FooBar)
add_library(KF5::FooBar ALIAS KF5FooBar)

target_include_directories(KF5FooBar INTERFACE "$<INSTALL_INTERFACE:${INCLUDE_INSTALL_DIR}/FooBar>")

target_link_libraries(KF5FooBar
  PUBLIC
    Qt5::Core
  # PRIVATE
  #  KF5::CoreAddons
  #  Other private libs
)

set_target_properties(KF5FooBar
  PROPERTIES VERSION ${FOOBAR_VERSION_STRING}
  SOVERSION ${FOOBAR_SOVERSION}
)

ecm_generate_headers(
  MyClass

  MODULE_NAME FooBar
  REQUIRED_HEADERS FooBar_HEADERS
)

# Install files
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/FooBar DESTINATION ${INCLUDE_INSTALL_DIR} COMPONENT Devel)

install(TARGETS KF5FooBar
  EXPORT KF5FooBarTargets
  ${INSTALL_TARGETS_DEFAULT_ARGS}
)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/foobar_export.h
  ${FooBar_HEADERS}
  DESTINATION ${INCLUDE_INSTALL_DIR}/FooBar
  COMPONENT Devel
)
