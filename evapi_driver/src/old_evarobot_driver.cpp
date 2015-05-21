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
	char c_buffer[1024];
	char c_data[1024];
	
	int i_read_size = 0;
	int i_total_count = 0;
	
	
	char start_buffy[21] = "{\"topic\": \"bumper\", ";
	char stop_buffy[18] = ", \"op\": \"publish\"";
	
	
	// JSON Variables
	// ????? time stamp	
	string str_topic_name;
	// End JSON Variables
	
	im_msgs::Bumper bumper_msg;
	char send_data[1024] = "{ \"op\": \"subscribe\",  \"topic\": \"bumper\", \"type\": \"im_msgs/Bumper\", \"queue_length\": 10}";
	tcp_client.Write(send_data, sizeof(send_data));
	
	char send_data_imu[1024] = "{ \"op\": \"subscribe\",  \"topic\": \"sensor/imu\", \"type\": \"sensor_msgs/Imu\", \"queue_length\": 10}";
	tcp_client.Write(send_data_imu, sizeof(send_data_imu));

	
	char send_data_ir0[1024] = "{ \"op\": \"subscribe\",  \"topic\": \"sensor/ir0\", \"type\": \"sensor_msgs/Range\", \"queue_length\": 10}";
	tcp_client.Write(send_data_ir0, sizeof(send_data_ir0));

	char send_data_ir1[1024] = "{ \"op\": \"subscribe\",  \"topic\": \"sensor/ir1\", \"type\": \"sensor_msgs/Range\", \"queue_length\": 10}";
	tcp_client.Write(send_data_ir1, sizeof(send_data_ir1));

	char send_data_ir2[1024] = "{ \"op\": \"subscribe\",  \"topic\": \"sensor/ir2\", \"type\": \"sensor_msgs/Range\", \"queue_length\": 10}";
	tcp_client.Write(send_data_ir2, sizeof(send_data_ir2));			
	
	char send_data_sonar0[1024] = "{ \"op\": \"subscribe\",  \"topic\": \"sensor/sonar0\", \"type\": \"sensor_msgs/Range\", \"queue_length\": 10}";
	tcp_client.Write(send_data_sonar0, sizeof(send_data_sonar0));
	
	cout << "while giriliyor.." << endl;
	while (ros::ok())
	{
//		int Read(char * p_c_buffer, int i_size);

		cout << "REad.........." << endl;
		
		i_read_size = tcp_client.Read(c_buffer, 1024);
		
		cout << "DAta Size:  " << i_read_size << endl; 
				
		
		if(memcmp(start_buffy, &c_buffer[0], sizeof(start_buffy) - 1) == 0)
		{
			printf("New data starts\n");
			i_total_count = 0;
			
			// Cleaning data
			memset(c_data, 0, 1024);
			
			memcpy(&c_data[i_total_count], c_buffer, i_read_size);
			i_total_count += i_read_size;
			
		}
		else
		{
			if(i_read_size + i_total_count >= 1024)
			{
				memcpy(&c_data[i_total_count], c_buffer, 1024 - i_total_count);
				i_total_count = 1024;
				
				printf("Warning: Buffer is overloaded... %d\n", i_read_size + i_total_count);
				
			}
			else
			{
				memcpy(&c_data[i_total_count], c_buffer, i_read_size);
				i_total_count += i_read_size;
			}
						
		}
		
		printf("Total Count : %d\n", i_total_count);
		
//			for(int i = 0; i < sizeof(stop_buffy) - 1; i++)
//			{
//				printf("Stop buffy: %c, Buffer: %c \n", stop_buffy[i], data[totalcnt - 18 + i]);
//			}
		
		// Stop bytes are OK !
		if(memcmp(stop_buffy, &c_data[i_total_count - 18], sizeof(stop_buffy) - 1) == 0)
		{
			i_total_count = 0;
			im_msgs::BumperState bumper_state_dummy;
			
			// Parsing data.
			Json::Reader reader;
			Json::Value root;
			
			reader.parse(c_data, root);
			
//			std::cout << root << std::endl;
						
			str_topic_name = root.get("topic", "bumper" ).asString();;
			bumper_msg.header.frame_id = root["msg"]["header"].get("frame_id", "bumper_frame").asString();
			bumper_msg.header.seq = root["msg"]["header"].get("seq", 3).asInt();
			
			bumper_msg.header.stamp = ros::Time::now();
			
			const Json::Value states = root["msg"]["state"];
			
			for(int i = 0; i < states.size(); i++)
			{
				bumper_state_dummy.bumper_state = states[i]["bumper_state"].asBool();
				
				bumper_msg.state.push_back(bumper_state_dummy);
			}

			// PrintData
			cout << "TOPIC_NAME: " << str_topic_name << endl;
			cout << "FRAME_ID: " << bumper_msg.header.frame_id << endl;
			cout << "SEQ: " << bumper_msg.header.seq << endl;
			
			for(int i = 0; i < bumper_msg.state.size(); i++)
			{
				cout << "[" << i << "] --> " << bumper_msg.state[i].bumper_state << endl;
			}
			
			
		}
		
		std::cout << c_buffer << std::endl;
		printf("Client-read() is OK\n");

			
		memset(c_buffer, 0, 1024);
		

		// Veri topikten basılıyor.
		if(pose_bumper.getNumSubscribers() > 0 || b_always_on)
		{
			pose_bumper.publish(bumper_msg);
		}

		bumper_msg.state.clear();

		ros::spinOnce();

		// Frekansı tutturmak için uyutuluyor.
		loop_rate.sleep();
	}

	return 0;
}

