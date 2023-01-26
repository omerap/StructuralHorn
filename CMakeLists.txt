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

if (0)
if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET StructuralHorn PROPERTY CXX_STANDARD 20)
endif()
endif()

find_package(Boost 1.61 REQUIRED program_options)
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


find_package(Java REQUIRED)
set(JAVA_AWT_LIBRARY NotNeeded)
if (APPLE)
    set(JAVA_JVM_LIBRARY "${JVM_CUSTOM_LIB}")
endif()
#set(JAVA_INCLUDE_PATH2 NotNeeded)
set(JAVA_AWT_INCLUDE_PATH NotNeeded)
if(APPLE)
    set(CMAKE_FRAMEWORK_PATH "${JAVA_JVM_LIBRARY}")
    SET(JAVA_INCLUDE_PATH2 "$ENV{JAVA_HOME}/include")
endif()
find_package(JNI REQUIRED)
if (JNI_FOUND)
    message (STATUS "JAVA_HOME=$ENV{JAVA_HOME}")
    message (STATUS "JNI_INCLUDE_DIRS=${JNI_INCLUDE_DIRS}")
    message (STATUS "JNI_LIBRARIES=${JNI_LIBRARIES}")
    message(STATUS "JAVA_JVM_LIBRARY=${JAVA_JVM_LIBRARY}")
endif()

include(UseJava)

if (APPLE)
    include_directories(${JAVA_INCLUDE_PATH}/darwin)
endif()
include_directories(${JNI_INCLUDE_DIRS})

# Include sub-projects.
add_subdirectory ("src")
