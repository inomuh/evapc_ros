cmake_minimum_required(VERSION 2.8.3)
project(evarobot_description)


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



include_directories(
  ${catkin_INCLUDE_DIRS}
)


## Plugins
add_library(im_gazebo_ros_bumper src/im_gazebo_ros_bumper.cpp)
add_dependencies(im_gazebo_ros_bumper gazebo_msgs_gencpp)
target_link_libraries(im_gazebo_ros_bumper ${GAZEBO_LIBRARIES} ${Boost_LIBRARIES} ContactPlugin ${catkin_LIBRARIES})

add_library(evarobot_ros_bumper src/evarobot_ros_bumper.cpp)
target_link_libraries(evarobot_ros_bumper  ${catkin_LIBRARIES}  ${GAZEBO_LIBRARIES})

add_library(im_gazebo_ros_sonar src/im_gazebo_ros_sonar.cpp)
target_link_libraries(im_gazebo_ros_sonar ${GAZEBO_LIBRARIES} ${catkin_LIBRARIES})
add_dependencies(im_gazebo_ros_sonar ${PROJECT_NAME}_gencfg)


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
