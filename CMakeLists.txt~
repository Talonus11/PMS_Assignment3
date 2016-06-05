# The minimum version of CMake Required 
cmake_minimum_required (VERSION 2.6)

# Any ppoject name will suffice, this has connotaions when using advanced CMake Features
project (Assignment2_11377773_Chris_Schiller)

# CMake will now create the Makefiles that are needed to make an executable "main" that requires "main.cpp" and "lidar.cpp" 
add_executable(Assignment2 main.cpp ranger.cpp rangerfusion.cpp radar.cpp sonar.cpp laser.cpp generator.cpp)

add_definitions(-std=c++11)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread") #used for c++11 and STL stuff




