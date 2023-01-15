# CMakeList.txt : CMake project for StructHorn, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (StructHorn "StructHorn.cpp" "StructHorn.h" "Hypergraph.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET StructHorn PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
