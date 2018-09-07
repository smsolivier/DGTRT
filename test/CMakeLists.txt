list(APPEND TESTS
	matrix.cpp
	quadrature.cpp
	poly1d.cpp
	integrators.cpp
	sweep.cpp
	coefficient.cpp
	array.cpp
	transport.cpp
	)

if (CMAKE_TESTING_ENABLED)
foreach(test ${TESTS}) 
	get_filename_component(name ${test} NAME) 
	string (REPLACE ".cpp" "" ename ${name}) 
	add_executable(${ename} ${test}) 
	target_link_libraries(${ename} ${LIBS}) 
	add_test(${ename} ${ename})
endforeach() 
endif()
