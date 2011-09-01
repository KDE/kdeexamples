project(updatechecker)

include_directories(${KDE4_INCLUDES} ${QT_INCLUDES})

set(updatechecker_SRCS updatechecker.cpp main.cpp)

kde4_add_executable(updatechecker ${updatechecker_SRCS})
target_link_libraries(updatechecker ${KDE4_KDEUI_LIBS} ${KDE4_KNEWSTUFF3_LIBS})

install(TARGETS updatechecker ${INSTALL_TARGETS_DEFAULT_ARGS})
install(FILES ${updatechecker_SRCS} updatechecker.h README DESTINATION ${DATA_INSTALL_DIR}/kdeexamples/knewstuff/updatechecker)
