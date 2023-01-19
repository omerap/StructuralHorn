# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("StructuralHorn")

set(Boost_INCLUDE_DIR "C:/Program Files/boost/boost_1_81_0")
set(Boost_LIBRARY_DIR "C:/Program Files/boost/boost_1_81_0/stage/lib")
find_package(Boost 1.77)
if (Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIR})
	link_directories(${Boost_LIBRARY_DIR})
endif ()

# Include sub-projects.
add_subdirectory ("src")
