find_package(Phonon REQUIRED)
include_directories(${PHONON_INCLUDES} ${QT_INCLUDES})

macro(PHONON_DECLARE_EXAMPLES)
   foreach(_examplename ${ARGN})
      set(_SRCS ${_examplename}.cpp)
      automoc4_add_executable(${_examplename} ${_SRCS})
      target_link_libraries(${_examplename} ${PHONON_LIBS})
   endforeach(_examplename)
endmacro(PHONON_DECLARE_EXAMPLES)

phonon_declare_examples(
    tutorial1
    tutorial2
    tutorial3
    tutorial4
    outputselector
    #videoplayer
    #crossfade
    #videoplayandforget
    #pcmoutput
    #videoplayback
    )

