list(APPEND SRCS
	Error.cpp
	Quadrature.cpp
	)

list(APPEND HDRS
	Error.hpp
	Array.hpp
	Quadrature.hpp
	)

convert_filenames_to_full_paths(SRCS)
convert_filenames_to_full_paths(HDRS)

set(SOURCES ${SOURCES} ${SRCS} PARENT_SCOPE)
set(HEADERS ${HEADERS} ${HDRS} PARENT_SCOPE)
