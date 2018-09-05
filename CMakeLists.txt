cmake_minimum_required(VERSION 3.0) 
project(TRT) 
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -ffast-math -g")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

# find lua 
find_package(Lua REQUIRED)
include_directories(${LUA_INCLUDE_DIR}) 
if (LUA_FOUND)
  set(USE_LUA ON) 
  set(LUA_DIR "${PROJECT_SOURCE_DIR}/lua") 
endif()

# find openmp 
option(OMP "use OpenMP" ON) 
if (${OMP}) 
  find_package(OpenMP) 
endif()
if (OpenMP_FOUND) 
  set(USE_OMP ON) 
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

find_package(LAPACK)
if (LAPACK_FOUND)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -llapack")  
  message("link = ${LAPACK_LINKER_FLAGS}")
  message("libraries = ${LAPACK_LIBRARIES}")
endif()

option(USE_EIGEN "compile with eigen" ON) 

find_package(Libunwind) 
if (LIBUNWIND_FOUND) 
  include_directories(${LIBUNWIND_INCLUDE_DIR}) 
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -ldl")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl")
  set(USE_UNWIND "use backtracing" ON) 
endif()

set(TEST_DIR "${PROJECT_SOURCE_DIR}/test")
set(EXEC_DIR "${PROJECT_SOURCE_DIR}/exec") 

if (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()
message("build type = " ${CMAKE_BUILD_TYPE})

# A handy function to add the current source directory to a local
# filename. To be used for creating a list of sources.
function(convert_filenames_to_full_paths NAMES)
  unset(tmp_names)
  foreach(name ${${NAMES}})
    list(APPEND tmp_names ${CMAKE_CURRENT_SOURCE_DIR}/${name})
  endforeach()
  set(${NAMES} ${tmp_names} PARENT_SCOPE)
endfunction()

set(CMAKE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# to find configure file 
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${PROJECT_SOURCE_DIR}) 
include_directories(utils utils/eigen)
include_directories(general linalg fem)  

# store all head and sources 
set(SOURCES "") 
set(HEADERS "") 
add_subdirectory(general)
add_subdirectory(linalg)
add_subdirectory(fem) 

option(USE_WARNINGS "Enable warning messages" ON) 
option(ENABLE_CHECKS "enable checks" ON)
option(TESTING "compile and run tests" ON) 
set(MESH_DIR "${PROJECT_SOURCE_DIR}/data")
set(DIM 3)
set(INTEGRATION_ORDER 8)
set(INTEGRATION_TYPE LEGENDRE)
option(CH_TIMER "turn on CH_Timer" ON)
if (CH_TIMER)
  set(CH_NTIMER=OFF)
else()
  set(CH_NTIMER "turn off ch timer" ON)
endif()
configure_file(${CMAKE_PATH}/config.hpp.in config.hpp @ONLY) 

enable_testing() 

add_library(trt ${SOURCES} ${HEADERS}) 
set(LIBS trt ${LUA_LIBRARIES} ${LIBUNWIND_LIBRARIES} ${LAPACK_LIBRARIES} dl)  

add_subdirectory(test)
add_subdirectory(exec)

# build doxygen 
find_package(Doxygen)
if (DOXYGEN_FOUND) 
add_custom_target(doc ALL
	COMMAND Doxygen::doxygen Doxyfile &> /dev/null
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/docs
	)
endif()

