project(tutorial-kicon)
 
find_package(KDE4 REQUIRED)
include_directories(${KDE4_INCLUDES})
 
set(tutorial3_SRCS 
  main.cpp
  mainwindow.cpp
)

kde4_add_executable(tutorial-kicon ${tutorial3_SRCS})
 
target_link_libraries(tutorial-kicon ${KDE4_KDEUI_LIBS})
 
install(TARGETS tutorial-kicon DESTINATION ${BIN_INSTALL_DIR})
install(FILES tutorial-kiconui.rc 
        DESTINATION  ${DATA_INSTALL_DIR}/tutorial-kicon)
kde4_install_icons( ${ICON_INSTALL_DIR} )
