PROJECT( kde4start )
FIND_PACKAGE(KDE4 REQUIRED)
INCLUDE_DIRECTORIES( ${KDE4_INCLUDES} . )


SET(kde4startSources main.cpp )

KDE4_ADD_EXECUTABLE(kde4start ${kde4startSources} )

TARGET_LINK_LIBRARIES(kde4start ${KDE4_KDEUI_LIBS} ${KDE4_KCAL_LIBS} ${KDE4_KPARTS_LIBS} kdepim kcal_resourceremote )
