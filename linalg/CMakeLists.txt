list (APPEND SRCS
	 Matrix.cpp
	 Vector.cpp
	 )

list (APPEND HDRS
	 Matrix.hpp
	 Vector.hpp
	 )

convert_filenames_to_full_paths(SRCS) 
convert_filenames_to_full_paths(HDRS) 

set(SOURCES ${SOURCES} ${SRCS} PARENT_SCOPE)
set(HEADERS ${HEADERS} ${HDRS} PARENT_SCOPE) 
