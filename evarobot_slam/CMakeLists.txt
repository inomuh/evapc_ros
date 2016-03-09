cmake_minimum_required(VERSION 2.8.3)
project(evarobot_slam)

find_package(catkin REQUIRED COMPONENTS)
catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)

foreach(dir gazebo_map launch)
    install(DIRECTORY ${dir}/
        DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/${dir})
endforeach()
