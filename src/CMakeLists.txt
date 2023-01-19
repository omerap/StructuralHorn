# CMakeList.txt : CMake project for StructHorn, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (StructuralHorn "StructuralHorn.cpp" "StructuralHorn.h" "Hypergraph.h" "Global.h" "Global.cpp")

target_link_libraries( StructuralHorn ${Boost_LIBRARIES} )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET StructuralHorn PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
