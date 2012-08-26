project(nepomuk-test)

#find_package(KDE4 REQUIRED)
#find_package(NepomukCore REQUIRED)
#find_package(Soprano)
#find_package(SharedDesktopOntologies)

#include(SopranoAddOntology)
include(KDE4Defaults)

include_directories(
  ${QT_INCLUDES}
  ${KDE4_INCLUDES}
  ${SOPRANO_INCLUDE_DIR}
  ${CMAKE_SOURCE_DIR}
  ${SOPRANO_INCLUDE_DIR}
  ${NEPOMUK_CORE_INCLUDE_DIR}
  )

set( SRCS
  main.cpp
)

#nepomuk2_add_ontology_classes (SRCS
#    ONTOLOGIES
#    ${SHAREDDESKTOPONTOLOGIES_ROOT_DIR}/nie/nie.trig
#    ${SHAREDDESKTOPONTOLOGIES_ROOT_DIR}/nie/nco.trig
#    ${SHAREDDESKTOPONTOLOGIES_ROOT_DIR}/pimo/pimo.trig
#    #   ${SHAREDDESKTOPONTOLOGIES_ROOT_DIR}/nie/nfo.trig
#    #   ${SHAREDDESKTOPONTOLOGIES_ROOT_DIR}/nie/nmo.trig
#)

kde4_add_executable(nepomuk-test ${SRCS})

target_link_libraries( nepomuk-test
  ${KDE4_KDEUI_LIBS}
  ${KDE4_KIO_LIBS}
  ${NEPOMUK_CORE_LIBRARY}
  ${SOPRANO_LIBRARIES}
  )

install(TARGETS nepomuk-test
        DESTINATION ${BIN_INSTALL_DIR})
