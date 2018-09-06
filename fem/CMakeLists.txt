list(APPEND SRCS
  Basis.cpp
  Element.cpp
  ElTrans.cpp
  Node.cpp
  L2Segment.cpp
  FESpace.cpp
  BilinearIntegrator.cpp
  )

list(APPEND HDRS
  Basis.hpp
  Element.hpp
  ElTrans.hpp
  Node.hpp
  L2Segment.hpp
  FESpace.hpp
  BilinearIntegrator.hpp
  Coefficient.hpp
  )

convert_filenames_to_full_paths(SRCS)
convert_filenames_to_full_paths(HDRS)

set(SOURCES ${SOURCES} ${SRCS} PARENT_SCOPE)
set(HEADERS ${HEADERS} ${HDRS} PARENT_SCOPE)
