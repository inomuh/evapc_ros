cmake_minimum_required(VERSION 2.8.3)
project(evarobot_slam)


find_package(catkin REQUIRED COMPONENTS
  rplidar_ros
  teleop_twist_keyboard
)


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES evarobot_slam
#  CATKIN_DEPENDS rplidar_ros teleop_twist_keyboard
#  DEPENDS system_lib
)


include_directories(
  ${catkin_INCLUDE_DIRS}
)
