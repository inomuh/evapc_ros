cmake_minimum_required(VERSION 2.8.3)
project(evarobot_state_publisher)

find_package(catkin REQUIRED COMPONENTS
  nav_msgs
  roscpp
  rospy
  tf
)


catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)


add_executable(odom_to_base src/odom_to_base.cpp)


 target_link_libraries(odom_to_base
   ${catkin_LIBRARIES}
 )
 
 install(TARGETS odom_to_base
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)


foreach(dir launch)
    install(DIRECTORY ${dir}/
        DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/${dir})
endforeach()
