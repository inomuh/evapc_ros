cmake_minimum_required(VERSION 2.8.3)
project(evarobot_navigation)


find_package(catkin REQUIRED COMPONENTS
  move_base
  roscpp
)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)

foreach(dir launch map params rviz scripts)
    install(DIRECTORY ${dir}/
        DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/${dir})
endforeach()

