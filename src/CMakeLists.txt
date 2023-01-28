# CMakeList.txt : CMake project for StructHorn, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (StructuralHorn "StructuralHorn.cpp" "Global.cpp" "Stats.cpp")

link_directories()
target_link_libraries( StructuralHorn ${Boost_LIBRARIES} ${Z3_LIBRARY} ${JAVA_JVM_LIBRARY})
#target_link_libraries( StructuralHorn ${Boost_LIBRARIES} ${Z3_LIBRARY} "-framework JavaVM")

# TODO: Add tests and install targets if needed.
