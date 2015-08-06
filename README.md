# evapc ros
** Installing evapc_ros **<br \>

$ sudo apt-get install ros-indigo-navigation <br \>
$ cd ~/catkin_ws/src <br \>
$ git clone https://github.com/robopeak/rplidar_ros.git -b slam <br \>
$ sudo apt-get install ros-indigo-teleop-twist-keyboard <br \>
$ git clone https://github.com/ros-simulation/gazebo_ros_pkgs.git -b indigo-devel <br \>
$ git clone https://github.com/ros-controls/ros_control.git -b indigo-devel <br \>
$ git clone https://github.com/tu-darmstadt-ros-pkg/hector_gazebo.git -b indigo-devel <br \>
$ cd ~/catkin_ws <br \>
$ catkin_make <br \>
$ cd ~/catkin_ws/src <br \>
$ git clone https://github.com/inomuh/evapc_ros.git -b eva50 <br \>
$ catkin_make <br \>

** To run move_base ** <br \>
$ roslaunch evarobot_description evarobot.launch <br \>
$ roslaunch evarobot_navigation move_base.launch <br \>
