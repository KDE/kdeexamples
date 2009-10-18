project (opencollaborationexample)

include_directories(${KDE4_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR}/lib)


set(opencollaborationexample_SRCS
    main.cpp
    mainwindow.cpp
    simplepersonrequest.cpp
    contentdownload.cpp
)

kde4_add_ui_files(opencollaborationexample_SRCS
    contentdownload.ui
)

kde4_add_executable(opencollaborationexample ${opencollaborationexample_SRCS})
target_link_libraries(opencollaborationexample ocsclient ${KDE4_KIO_LIBS}  ${KDE4_KDEUI_LIBS})

