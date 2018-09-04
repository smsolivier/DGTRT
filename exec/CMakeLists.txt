list(APPEND EXEC

	)

# add_executable(poisson poisson.cpp)
# target_link_libraries(poisson fem) 
foreach(file ${EXEC})
	get_filename_component(name ${file} NAME)
	string (REPLACE ".cpp" "" ename ${name})
	add_executable(${ename} ${file})
	target_link_libraries(${ename} ${LIBS})
endforeach() 
