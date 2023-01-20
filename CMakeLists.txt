# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.15.0)

project ("StructuralHorn")

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR ) 
  message (FATAL_ERROR
    "In-source builds are not allowed. Please clean your source tree and try again.")  
endif()

# Add path for custom modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 14 CACHE STRING "C++ standard to conform to")
add_definitions(-D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS)

set(Boost_INCLUDE_DIR "C:/Program Files/boost/boost_1_81_0")
set(Boost_LIBRARY_DIR "C:/Program Files/boost/boost_1_81_0/stage/lib")
find_package(Boost 1.77)
if (Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIR})
	link_directories(${Boost_LIBRARY_DIR})
endif ()

find_package(Z3 4.8.12)
if (NOT Z3_FOUND)
  message(Error "No Z3 found.")
else()
  include_directories(${Z3_INCLUDE_DIR})
  message ("Found Z3 at ${Z3_EXECUTABLE}")
  # indicate that we want z3 binary to be included in the binary distribution
  install (PROGRAMS ${Z3_EXECUTABLE} DESTINATION bin)
endif()

# Include sub-projects.
add_subdirectory ("src")
