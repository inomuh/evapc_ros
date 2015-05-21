#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Vector3.h"
#include "geometry_msgs/Pose2D.h"
#include "im_msgs/Bumper.h"

#include <string>    
#include <sstream>

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>

#include <vector>

#include "evapi_driver/IMTCPClient.h"

#define BUFFER_SIZE 4096

using namespace std;

int main(int argc, char **argv)
{
		
	// ROS_Params
	int i_port_no;
	
	string str_server;
	string str_bumper_topic;
	
	double d_frequency;
	
	bool b_always_on;
	// end (ROS Params)
	
	ros::init(argc, argv, "evapi_driver");
	ros::NodeHandle n;

	n.param<string>("evapi_driver/server", str_server, "evarobotDSK");
	n.param<string>("evapi_driver/topicBumper", str_bumper_topic, "bumper");

	
	n.param("evapi_driver/alwaysOn", b_always_on, false);

	if(!n.getParam("evapi_driver/portNo", i_port_no))
	{
	  ROS_ERROR("Failed to get param 'portNo'");
	} 	
	
	if(!n.getParam("evapi_driver/frequency", d_frequency))
	{
	  ROS_ERROR("Failed to get param 'frequency'");
	} 
	
		

	ros::Publisher pose_bumper = n.advertise<im_msgs::Bumper>(str_bumper_topic.c_str(), 10);

	ros::Rate loop_rate(d_frequency);


	IMTCPClient tcp_client(str_server, i_port_no);
	IMTCPClient tcp_client_pc("localhost", i_port_no);
	
	char c_buffer_low[BUFFER_SIZE];
	char c_buffer_high[BUFFER_SIZE];
	
	
	im_msgs::Bumper bumper_msg;
	char send_data[1024] = "{ \"op\": \"subscribe\",  \"topic\": \"bumper\", \"type\": \"im_msgs/Bumper\", \"queue_length\": 10}";
	char pub_bumper[1024] = "{ \"op\": \"advertise\", \"topic\": \"bumper\", \"type\": \"im_msgs/Bumper\"}";
	tcp_client.Write(send_data, sizeof(send_data));
	tcp_client_pc.Write(pub_bumper, sizeof(pub_bumper));
	
	char send_data_imu[1024] = "{ \"op\": \"subscribe\",  \"topic\": \"sensor/imu\", \"type\": \"sensor_msgs/Imu\", \"queue_length\": 10}";
	char pub_imu[1024] = "{ \"op\": \"advertise\", \"topic\": \"sensor/imu\", \"type\": \"sensor_msgs/Imu\"}";
	tcp_client.Write(send_data_imu, sizeof(send_data_imu));
	tcp_client_pc.Write(pub_imu, sizeof(pub_imu));

	
	char send_data_ir0[1024] = "{ \"op\": \"subscribe\",  \"topic\": \"sensor/ir0\", \"type\": \"sensor_msgs/Range\", \"queue_length\": 10}";
	char pub_ir0[1024] = "{ \"op\": \"advertise\", \"topic\": \"sensor/ir0\", \"type\": \"sensor_msgs/Range\"}";
	tcp_client.Write(send_data_ir0, sizeof(send_data_ir0));
	tcp_client_pc.Write(pub_ir0, sizeof(pub_ir0));

	char send_data_ir1[1024] = "{ \"op\": \"subscribe\",  \"topic\": \"sensor/ir1\", \"type\": \"sensor_msgs/Range\", \"queue_length\": 10}";
	char pub_ir1[1024] = "{ \"op\": \"advertise\", \"topic\": \"sensor/ir1\", \"type\": \"sensor_msgs/Range\"}";
	tcp_client.Write(send_data_ir1, sizeof(send_data_ir1));
	tcp_client_pc.Write(pub_ir1, sizeof(pub_ir1));
	
	char send_data_ir2[1024] = "{ \"op\": \"subscribe\",  \"topic\": \"sensor/ir2\", \"type\": \"sensor_msgs/Range\", \"queue_length\": 10}";
	char pub_ir2[1024] = "{ \"op\": \"advertise\", \"topic\": \"sensor/ir2\", \"type\": \"sensor_msgs/Range\"}";
	tcp_client.Write(send_data_ir2, sizeof(send_data_ir2));
	tcp_client_pc.Write(pub_ir2, sizeof(pub_ir2));			
	
	char send_data_sonar0[1024] = "{ \"op\": \"subscribe\",  \"topic\": \"sensor/sonar0\", \"type\": \"sensor_msgs/Range\", \"queue_length\": 10}";
	char pub_sonar0[1024] = "{ \"op\": \"advertise\", \"topic\": \"sensor/sonar0\", \"type\": \"sensor_msgs/Range\"}";
	tcp_client_pc.Write(pub_sonar0, sizeof(pub_sonar0));
	tcp_client.Write(send_data_sonar0, sizeof(send_data_sonar0));
	
	char send_data_odom[1024] = "{ \"op\": \"subscribe\",  \"topic\": \"odom\", \"type\": \"nav_msgs/Odometry\", \"queue_length\": 10}";
	char pub_odom[1024] = "{ \"op\": \"advertise\", \"topic\": \"odom\", \"type\": \"nav_msgs/Odometry\"}";
	tcp_client_pc.Write(pub_odom, sizeof(pub_odom));
	tcp_client.Write(send_data_odom, sizeof(send_data_odom));
	
	char send_data_vel[1024] = "{ \"op\": \"subscribe\",  \"topic\": \"cmd_vel\", \"type\": \"geometry_msgs/Twist\", \"queue_length\": 10}";
//	tcp_client_pc.Write(send_data_vel, sizeof(send_data_vel));
	
	
	
	
//	"{ \"op\": \"advertise\", \"topic\": \"cmd_vel\", \"type\": \"geometry_msgs/Twist\"}"
	
	cout << "while giriliyor.." << endl;
	
	// thread yapılarak
	// ikisi farklı thread'larda çalıştırılabilir.
	while (ros::ok())
	{
		// Theread 1
		tcp_client.Read(c_buffer_low, BUFFER_SIZE);
		tcp_client_pc.Write(c_buffer_low, sizeof(c_buffer_low));
		cout << c_buffer_low << endl << endl;
		memset(c_buffer_low, 0, BUFFER_SIZE);
		
		
		// Theread 2
//		tcp_client_pc.Read(c_buffer_high, 1024);
//		tcp_client.Write(c_buffer_high, sizeof(c_buffer_high));
		memset(c_buffer_high, 0, BUFFER_SIZE);
		

		ros::spinOnce();

		// Frekansı tutturmak için uyutuluyor.
		loop_rate.sleep();
	}

	return 0;
}

