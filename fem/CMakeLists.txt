list(APPEND SRCS
  Basis.cpp
  )

list(APPEND HDRS
  Basis.hpp
  )

convert_filenames_to_full_paths(SRCS)
convert_filenames_to_full_paths(HDRS)

set(SOURCES ${SOURCES} ${SRCS} PARENT_SCOPE)
set(HEADERS ${HEADERS} ${HDRS} PARENT_SCOPE)
