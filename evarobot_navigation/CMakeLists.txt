cmake_minimum_required(VERSION 2.8.3)
project(evarobot_navigation)


find_package(catkin REQUIRED COMPONENTS
  move_base
  roscpp
)


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES evarobot_navigation
#  CATKIN_DEPENDS move_base roscpp
#  DEPENDS system_lib
)


include_directories(
  ${catkin_INCLUDE_DIRS}
)

install(DIRECTORY launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
  )

install(DIRECTORY map
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
  )
  
install(DIRECTORY params
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
  )
  
install(DIRECTORY rviz
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
  )  
