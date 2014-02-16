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
#    PRIVATE
#        KF5::CoreAddons
        # Other private libs
)

set_target_properties(KF5FooBar
    PROPERTIES VERSION ${FOOBAR_VERSION_STRING}
    SOVERSION ${FOOBAR_SOVERSION}
    EXPORT_NAME "FooBar"
)

ecm_generate_headers(FooBar_HEADERS
  HEADER_NAMES
    MyClass
    # other classes

    REQUIRED_HEADERS FooBar_HEADERS
)

# Install files
install(TARGETS KF5FooBar
        EXPORT KF5FooBarTargets
        ${INSTALL_TARGETS_DEFAULT_ARGS})

install(FILES
            ${CMAKE_CURRENT_BINARY_DIR}/foobar_export.h
            ${FooBar_HEADERS}
        DESTINATION ${INCLUDE_INSTALL_DIR}/FooBar
        COMPONENT Devel)

include(ECMGeneratePriFile)
ecm_generate_pri_file(
    BASE_NAME FooBar
    LIB_NAME KF5FooBar
    DEPS "core"
    FILENAME_VAR PRI_FILENAME
)
install(FILES ${PRI_FILENAME}
        DESTINATION ${ECM_MKSPECS_INSTALL_DIR})
