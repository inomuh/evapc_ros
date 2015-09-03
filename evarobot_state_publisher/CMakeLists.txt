cmake_minimum_required(VERSION 2.8.3)
project(evarobot_state_publisher)

find_package(catkin REQUIRED COMPONENTS
#  evarobot_description
  nav_msgs
#  robot_state_publisher
  roscpp
  rospy
  tf
)


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES evarobot_state_publisher
#  CATKIN_DEPENDS evarobot_description nav_msgs robot_state_publisher roscpp rospy tf
#  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)


add_executable(odom_to_base src/odom_to_base.cpp)


 target_link_libraries(odom_to_base
   ${catkin_LIBRARIES}
 )

install(DIRECTORY launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
  )
  
install(DIRECTORY rviz
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
  )
  
install(DIRECTORY urdf
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
  )
