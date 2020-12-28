cmake_minimum_required(VERSION 2.8.3)
project(router)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  message_generation
  protocol_msgs
  controller_msgs
  simulation_msgs
)

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES pololu-3pi-comm
#  CATKIN_DEPENDS roscpp
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(unity_node src/unity_router.cpp)
add_dependencies(unity_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(unity_node ${catkin_LIBRARIES})

add_executable(xbee_node src/xbee_router.cpp)
add_dependencies(xbee_node ${${PROJECT_name}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(xbee_node ${catkin_LIBRARIES})
