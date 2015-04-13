cmake_minimum_required(VERSION 2.8.3)
project(evarobot_description)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  urdf
  message_generation 
  gazebo_msgs 
  roscpp 
  rospy 
  nodelet 
  angles 
  std_srvs 
  geometry_msgs 
  sensor_msgs 
  nav_msgs 
  urdf 
  tf 
  tf2_ros 
  dynamic_reconfigure 
  driver_base 
  rosgraph_msgs 
  trajectory_msgs 
  image_transport 
  rosconsole
  cv_bridge
  polled_camera
  diagnostic_updater
  camera_info_manager
)

include (FindPkgConfig)
if (PKG_CONFIG_FOUND)
  pkg_check_modules(XML libxml-2.0)
  pkg_check_modules(OGRE OGRE)
  pkg_check_modules(OGRE-Terrain OGRE-Terrain)
  pkg_check_modules(OGRE-Paging OGRE-Paging)
else()
  message(FATAL_ERROR "pkg-config is required; please install it")
endif()

# Depend on system install of Gazebo and SDFormat
find_package(gazebo REQUIRED)
find_package(Boost REQUIRED COMPONENTS thread)

execute_process(COMMAND
  pkg-config --variable=plugindir OGRE
  OUTPUT_VARIABLE OGRE_PLUGIN_PATH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)


## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
#catkin_python_setup()


generate_dynamic_reconfigure_options(
  cfg/CameraSynchronizer.cfg
  cfg/GazeboRosCamera.cfg
  cfg/GazeboRosOpenniKinect.cfg
  cfg/Hokuyo.cfg
)

include_directories(include
  ${Boost_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS}
  ${GAZEBO_INCLUDE_DIRS}
  ${OGRE_INCLUDE_DIRS}
  ${OGRE-Terrain_INCLUDE_DIRS}
  ${OGRE-Paging_INCLUDE_DIRS}
  include
)

link_directories(
  ${GAZEBO_LIBRARY_DIRS}
  ${OGRE_LIBRARY_DIRS}
  ${OGRE-Terrain_LIBRARY_DIRS}
  ${OGRE-Paging_LIBRARY_DIRS}
)



################################################
## Declare ROS messages, services and actions ##
################################################

## To declare and build messages, services or actions from within this
## package, follow these steps:
## * Let MSG_DEP_SET be the set of packages whose message types you use in
##   your messages/services/actions (e.g. std_msgs, actionlib_msgs, ...).
## * In the file package.xml:
##   * add a build_depend and a run_depend tag for each package in MSG_DEP_SET
##   * If MSG_DEP_SET isn't empty the following dependencies might have been
##     pulled in transitively but can be declared for certainty nonetheless:
##     * add a build_depend tag for "message_generation"
##     * add a run_depend tag for "message_runtime"
## * In this file (CMakeLists.txt):
##   * add "message_generation" and every package in MSG_DEP_SET to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * add "message_runtime" and every package in MSG_DEP_SET to
##     catkin_package(CATKIN_DEPENDS ...)
##   * uncomment the add_*_files sections below as needed
##     and list every .msg/.srv/.action file to be processed
##   * uncomment the generate_messages entry below
##   * add every package in MSG_DEP_SET to generate_messages(DEPENDENCIES ...)

## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
# generate_messages(
#   DEPENDENCIES
#   std_msgs  # Or other packages containing msgs
# )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES 
  vision_reconfigure 
#  gazebo_ros_utils 
#  gazebo_ros_camera_utils 
#  gazebo_ros_camera 
#  gazebo_ros_multicamera 
#  gazebo_ros_depth_camera 
#  gazebo_ros_openni_kinect 
#  gazebo_ros_gpu_laser 
#  gazebo_ros_laser 
#  gazebo_ros_block_laser 
#  gazebo_ros_p3d 
#  gazebo_ros_imu 
#  gazebo_ros_f3d 
#  gazebo_ros_ft_sensor
  im_gazebo_ros_bumper 
#  gazebo_ros_template 
#  gazebo_ros_projector 
#  gazebo_ros_prosilica 
#  gazebo_ros_force 
#  gazebo_ros_joint_trajectory 
#  gazebo_ros_joint_state_publisher 
#  gazebo_ros_joint_pose_trajectory
#  gazebo_ros_diff_drive
#  gazebo_ros_tricycle_drive
#  gazebo_ros_skid_steer_drive
#  gazebo_ros_video
#  gazebo_ros_planar_move
  
  CATKIN_DEPENDS 
  message_generation 
  gazebo_msgs 
  roscpp 
  rospy 
  nodelet 
  angles 
  std_srvs 
  geometry_msgs 
  sensor_msgs 
  nav_msgs 
  urdf 
  tf 
  tf2_ros
  dynamic_reconfigure 
  driver_base 
  rosgraph_msgs 
  trajectory_msgs 
  image_transport 
  rosconsole
  camera_info_manager
  DEPENDS 
    gazebo 
    SDF
  )

add_dependencies(${PROJECT_NAME}_gencfg ${catkin_EXPORTED_TARGETS})


###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
)

## Declare a cpp library
# add_library(evarobot_description
#   src/${PROJECT_NAME}/evarobot_description.cpp
# )

## Declare a cpp executable
# add_executable(evarobot_description_node src/evarobot_description_node.cpp)

## Plugins
add_library(im_gazebo_ros_bumper src/im_gazebo_ros_bumper.cpp)
add_dependencies(im_gazebo_ros_bumper gazebo_msgs_gencpp)
target_link_libraries(im_gazebo_ros_bumper ${GAZEBO_LIBRARIES} ${Boost_LIBRARIES} ContactPlugin ${catkin_LIBRARIES})

add_library(evarobot_ros_bumper src/evarobot_ros_bumper.cpp)
target_link_libraries(evarobot_ros_bumper  ${catkin_LIBRARIES}  ${GAZEBO_LIBRARIES})

add_library(im_gazebo_ros_sonar src/im_gazebo_ros_sonar.cpp)
target_link_libraries(im_gazebo_ros_sonar ${GAZEBO_LIBRARIES} ${catkin_LIBRARIES})
add_dependencies(im_gazebo_ros_sonar ${PROJECT_NAME}_gencfg)



## Add cmake target dependencies of the executable/library
## as an example, message headers may need to be generated before nodes
# add_dependencies(evarobot_description_node evarobot_description_generate_messages_cpp)

## Specify libraries to link a library or executable target against
# target_link_libraries(evarobot_description_node
#   ${catkin_LIBRARIES}
# )

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )
install(TARGETS 
#  hokuyo_node 
#  vision_reconfigure 
#  camera_synchronizer
#  gazebo_ros_utils
#  gazebo_ros_camera_utils
#  gazebo_ros_camera
#  gazebo_ros_multicamera
#  MultiCameraPlugin
#  gazebo_ros_depth_camera
#  gazebo_ros_openni_kinect
#  gazebo_ros_openni_kinect
#  gazebo_ros_laser
#  gazebo_ros_block_laser
#  gazebo_ros_p3d
#  gazebo_ros_imu
#  gazebo_ros_f3d
#  gazebo_ros_ft_sensor
  im_gazebo_ros_bumper
#  gazebo_ros_hand_of_god
#  gazebo_ros_template
#  gazebo_ros_projector
#  gazebo_ros_prosilica
#  gazebo_ros_force
#  gazebo_ros_joint_trajectory
#  gazebo_ros_joint_state_publisher
#  gazebo_ros_joint_pose_trajectory
#  gazebo_ros_diff_drive
#  gazebo_ros_tricycle_drive
#  gazebo_ros_skid_steer_drive
#  gazebo_ros_video
#  gazebo_ros_planar_move
#  pub_joint_trajectory_test  
#  gazebo_ros_gpu_laser
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  )

install(DIRECTORY include/
   DESTINATION ${CATKIN_GLOBAL_INCLUDE_DESTINATION}
   FILES_MATCHING PATTERN "*.h"
)

install(PROGRAMS scripts/set_wrench.py scripts/set_pose.py scripts/gazebo_model
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
  )

install(DIRECTORY Media
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
  )

install(DIRECTORY test
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
  )

## Mark executables and/or libraries for installation
# install(TARGETS evarobot_description evarobot_description_node
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_evarobot_description.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
