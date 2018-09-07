list(APPEND SRCS
  TVector.cpp
  Opacity.cpp
  TransportOperator.cpp
  Sweeper.cpp
  )

list(APPEND HDRS
  TVector.hpp
  Opacity.hpp
  TransportOperator.hpp
  Sweeper.hpp
  )

convert_filenames_to_full_paths(SRCS)
convert_filenames_to_full_paths(HDRS)

set(SOURCES ${SOURCES} ${SRCS} PARENT_SCOPE)
set(HEADERS ${HEADERS} ${HDRS} PARENT_SCOPE)
