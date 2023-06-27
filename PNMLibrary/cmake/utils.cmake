MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH (child ${children})
    IF (IS_DIRECTORY ${curdir}/${child})
      LIST(APPEND dirlist ${child})
    ENDIF ()
  ENDFOREACH ()
  SET(${result} ${dirlist})
ENDMACRO()

MACRO(static_dependency_check lib_name)
  IF (PNM_ENABLE_STATIC_LIB_CHECK)
    set(dummy_lib_name "DUMMY_${lib_name}")
    add_library(${dummy_lib_name} MODULE /dev/null)
    target_link_libraries(${dummy_lib_name} PRIVATE -Wl,--no-undefined -Wl,--whole-archive ${lib_name} -Wl,--no-whole-archive)
  ENDIF()
ENDMACRO()
