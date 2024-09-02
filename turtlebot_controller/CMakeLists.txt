cmake_minimum_required(VERSION 3.0.2)
project(turtlebot_controller)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  rospy
  std_msgs
  turtlesim
)

## Declare a catkin package
catkin_package(
  CATKIN_DEPENDS geometry_msgs roscpp rospy std_msgs turtlesim
)

## Specify additional locations of header files
include_directories(
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ executable
add_executable(turtle_listener src/turtle_listener.cpp)

## Add cmake target dependencies of the executable
add_dependencies(turtle_listener ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
target_link_libraries(turtle_listener
  ${catkin_LIBRARIES}
)

add_executable(turtle_trajectory src/turtle_trajectory.cpp)
target_link_libraries(turtle_trajectory ${catkin_LIBRARIES})

