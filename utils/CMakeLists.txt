list (APPEND SRCS
	 WallTimer.cpp
	 CH_Timer.cpp
	 Lua.cpp
	 Writer.cpp
	 Timer.cpp
	 )

list (APPEND HDRS
	 WallTimer.hpp
	 CH_Timer.hpp
	 ClockTicks.hpp
	 Lua.hpp
	 Writer.hpp
	 Timer.hpp
	 )

convert_filenames_to_full_paths(SRCS) 
convert_filenames_to_full_paths(HDRS) 

set(SOURCES ${SOURCES} ${SRCS} PARENT_SCOPE)
set(HEADERS ${HEADERS} ${HDRS} PARENT_SCOPE) 
