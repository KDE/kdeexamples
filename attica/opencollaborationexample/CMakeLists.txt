project(opencollaborationexample)

include_directories(${KDE4_INCLUDES} ${LIBATTICA_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR})

set(opencollaborationexample_SRCS
    main.cpp
    mainwindow.cpp
    person.cpp
    contentdownload.cpp
    contentcreation.cpp
    privatedata.cpp
    )

set(opencollaborationexample_HEADERS
    contentcreation.h
    contentdownload.h
    mainwindow.h
    person.h
    privatedata.h
    )

set(opencollaborationexample_UI
    person.ui
    contentdownload.ui
    contentcreation.ui
    privatedata.ui
    )

install(FILES ${opencollaborationexample_SRCS} ${opencollaborationexample_HEADERS} ${opencollaborationexample_UI}
        DESTINATION ${DATA_INSTALL_DIR}/kdeexamples/attica/opencollaborationexample)

kde4_add_ui_files(opencollaborationexample_SRCS ${opencollaborationexample_UI})

kde4_add_executable(opencollaborationexample ${opencollaborationexample_SRCS})
target_link_libraries(opencollaborationexample ${LIBATTICA_LIBRARIES} ${KDE4_KIO_LIBS}  ${KDE4_KDEUI_LIBS})
install(TARGETS opencollaborationexample ${INSTALL_TARGETS_DEFAULT_ARGS})
