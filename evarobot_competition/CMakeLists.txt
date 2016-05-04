cmake_minimum_required(VERSION 2.8.3)
project(evarobot_competition)


find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  im_msgs
  roscpp
  rospy
)

catkin_package(INCLUDE_DIRS include)


include_directories(
  ${catkin_INCLUDE_DIRS}
  include
)

 add_executable(evarobot_competition src/evarobot_competition.cpp)
 add_dependencies(evarobot_competition im_msgs_generate_messages_cpp)
 target_link_libraries(evarobot_competition
   ${catkin_LIBRARIES}
)
