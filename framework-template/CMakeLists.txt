cmake_minimum_required(VERSION 2.8.12)

project(FooBar)

# ECM setup
find_package(ECM 0.0.10 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

include(FeatureSummary)
include(GenerateExportHeader)
include(ECMSetupVersion)
include(ECMGenerateHeaders)
include(ECMPackageConfigHelpers)
include(KDEInstallDirs)
include(KDEFrameworkCompilerSettings)
include(KDECMakeSettings)

set(KF5_VERSION "4.96.0") # Update this

ecm_setup_version(${KF5_VERSION}
    VARIABLE_PREFIX FOOBAR
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/foobar_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5FooBarConfigVersion.cmake"
)

# Dependencies
set(REQUIRED_QT_VERSION "5.2.0")

# Required Qt5 components to build this framework
find_package(Qt5 ${REQUIRED_QT_VERSION} NO_MODULE REQUIRED Core)

# TODO: Add all required find_package() calls here. For example:
# find_package(KF5CoreAddons ${KF5_VERSION} REQUIRED)

# TODO-i18n: Uncomment if your framework is translated using KI18n
# find_package(KF5I18n ${KF5_VERSION} REQUIRED)

# TODO-docbook: Uncomment if you want to provide docbook-based documentation
# find_package(KF5DocTools ${KF5_VERSION} REQUIRED)

# TODO-qt: Uncomment if your framework is translated using Qt
# include(ECMPoQmTools)

# Translations
# TODO-i18n: Uncomment if your framework is translated using KI18n
# add_definitions(-DTRANSLATION_DOMAIN=\"foobar5\")
if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/po")
    # TODO-i18n: Uncomment if your framework is translated using KI18n
    # ki18n_install(po)

    # TODO-qt: Uncomment if your framework is translated using Qt
    # ecm_install_po_files_as_qm(po)

    # TODO-docbook: Uncomment if you want to provide docbook-based documentation
    # kdoctools_install(po)
endif()

# Subdirectories
add_subdirectory(src)
add_subdirectory(autotests)
add_subdirectory(tests)

# Create a Config.cmake and a ConfigVersion.cmake file and install them
set(CMAKECONFIG_INSTALL_DIR "${CMAKECONFIG_INSTALL_PREFIX}/KF5FooBar")

ecm_configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KF5FooBarConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF5FooBarConfig.cmake"
    INSTALL_DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
)

install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/KF5FooBarConfig.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/KF5FooBarConfigVersion.cmake"
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel)

install(EXPORT KF5FooBarTargets
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        FILE KF5FooBarTargets.cmake
        NAMESPACE KF5::)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/foobar_version.h"
        DESTINATION "${INCLUDE_INSTALL_DIR}"
        COMPONENT Devel)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
