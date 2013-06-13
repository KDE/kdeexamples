find_package(KDeclarative REQUIRED)

include_directories( ${KDE4_INCLUDES} ${QT_INCLUDES} )

set(example-qmlapp_SRCS
    main.cpp
    exampleapp.cpp
    kdeclarativeview.cpp
)

kde4_add_executable(example-qmlapp ${example-qmlapp_SRCS})

target_link_libraries(example-qmlapp
    ${QT_QTDECLARATIVE_LIBRARY}
    ${QT_QTOPENGL_LIBRARY}
    ${QT_QTSCRIPT_LIBRARY}
    ${KDE4_KDEUI_LIBS}
    ${KDE4_KIO_LIBS}
    ${KDE4_PLASMA_LIBS}
    ${KDECLARATIVE_LIBRARIES}
)

install(TARGETS example-qmlapp ${INSTALL_TARGETS_DEFAULT_ARGS} )

