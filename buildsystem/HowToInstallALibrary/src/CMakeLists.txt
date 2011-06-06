# for the point of this example it doesn't matter whether this is a C or C++ library
# and whether add_library() or kde4_add_library() is used. So we use the most basic one:
add_library(bar SHARED bar.c)

# set version of the shared library
set_target_properties(bar PROPERTIES VERSION ${BAR_VERSION}
                                     SOVERSION ${BAR_VERSION_MAJOR} )

# install the headers
install(FILES bar.h DESTINATION ${INCLUDE_INSTALL_DIR} )

# install the library(s).
# The EXPORT keyword puts the target "bar" into a set of targets. In C++ this would look like
#    std::set<Targets> targetsToBeExported;
#    targetsToBeExported.insert(bar);
# This "export set" is then used in the toplevel CMakeLists.txt
# The three different destinations are mostly interesting for Windows:
# the dll must go into bin/ (needed at RUNTIME), while the lib-file is considered
# ARCHIVE and should go into lib/
install(TARGETS bar EXPORT BarExport LIBRARY DESTINATION ${LIB_INSTALL_DIR}
                                     ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
                                     RUNTIME DESTINATION ${BIN_INSTALL_DIR} )
