project (opencollaborationexample)

include_directories(${KDE4_INCLUDES} ${LIBATTICA_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR})

set(opencollaborationexample_SRCS
    main.cpp
    mainwindow.cpp
    person.cpp
    contentdownload.cpp
    contentcreation.cpp
    privatedata.cpp
)

kde4_add_ui_files(opencollaborationexample_SRCS
    person.ui
    contentdownload.ui
    contentcreation.ui
    privatedata.ui
)

kde4_add_executable(opencollaborationexample ${opencollaborationexample_SRCS})
target_link_libraries(opencollaborationexample ${LIBATTICA_LIBRARIES} ${KDE4_KIO_LIBS}  ${KDE4_KDEUI_LIBS})

