#include "evarobot_competition/evarobot_competition.h"

using namespace std;

struct OBJECT {
	geometry_msgs::Point pos;
	int color;
	bool isAchieved;
};

struct REPORT {
	int objectID;
	ros::Duration mytime;
	float distError;
};

int numberAchieved = 0;
double duration = 0.0, eps_pose = 0.0;
bool start_flag = false;
nav_msgs::Odometry robot_pose;
ros::Time begin;

vector <OBJECT> objects;
vector <REPORT> myreport;

bool AddObject(im_msgs::AddObject::Request  &req,
							 im_msgs::AddObject::Response &res)
{
  OBJECT dummy;
  
  dummy.pos = req.object_pose;
  dummy.color = req.color;
  dummy.isAchieved = false;
  
  objects.push_back(dummy);
	ROS_INFO("Added an Object");
	
	ROS_INFO_STREAM("X: " << dummy.pos.x << " Y: " << dummy.pos.y << " Z: " << dummy.pos.z << " Color: " << dummy.color << std::endl);

	res.ret = true;
	
  return true;
}

bool Start(std_srvs::Empty::Request& request, std_srvs::Empty::Response& response)
{
	start_flag = true;
	return true;
}

bool CheckObject(im_msgs::CheckObject::Request  &req,
								 im_msgs::CheckObject::Response &res)
{
	bool isCorrect = false;
	
	// Robotun pozisyonunu da kontrol et...
	// pose.z robotun büyüklüğü
  for(int i = 0; i < objects.size(); i++)
  {
		if( !(objects[i].isAchieved)
		&& req.color == objects[i].color
		&& req.object_pose.x < 1.5 * objects[i].pos.z + objects[i].pos.x 
		&& req.object_pose.x > - 1.5 * objects[i].pos.z + objects[i].pos.x
		&& req.object_pose.y < 1.5 * objects[i].pos.z + objects[i].pos.y 
		&& req.object_pose.y > - 1.5 * objects[i].pos.z + objects[i].pos.y)
		{
			float pos_dif_x = robot_pose.pose.pose.position.x - objects[i].pos.x;
			float pos_dif_y = robot_pose.pose.pose.position.y - objects[i].pos.y;
			
			if(sqrtf(pos_dif_x*pos_dif_x + pos_dif_y*pos_dif_y) <= eps_pose)
			{			
				// Rapor
				REPORT dummy;
				float diff_x = objects[i].pos.x - req.object_pose.x;
				float diff_y = objects[i].pos.y - req.object_pose.y;
				
				dummy.objectID = i;
				dummy.mytime = ros::Time::now() - begin;
				dummy.distError = sqrtf(diff_x*diff_x + diff_y*diff_y);
				myreport.push_back(dummy);			
				
				isCorrect = true;
				objects[i].isAchieved = true;
				
				numberAchieved++;
				break;			
			}
			
		}
	}
  
  res.ret = isCorrect;
  res.achieved = numberAchieved;
  res.remaining_time = duration*60.0 - (ros::Time::now() - begin).toSec(); // in sec
 
  return true;
}

float calcScore()
{
	return 100.0 * myreport.size() / objects.size();
}

void printReport()
{
	for(int i = 0; i < myreport.size(); i++)
	{
		ROS_INFO("-------------------------------------------");
		ROS_INFO("Object ID: %d", myreport[i].objectID);
		ROS_INFO_STREAM("Time: " << myreport[i].mytime.toSec() << "sec ");
		ROS_INFO("Distance Error: %f ", myreport[i].distError);
	}
	ROS_INFO("Your Score is: %f/100.0", calcScore());
}

void CallbackOdom(const nav_msgs::Odometry & msg)
{
	robot_pose = msg;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "evarobot_competition");
  ros::NodeHandle n;
    

	n.param("evarobot_competition/duration", duration, 5.0); // min.
	n.param("evarobot_competition/epsPose", eps_pose, 2.0); // m.

  ros::ServiceServer srv_add = n.advertiseService("evarobot_competition/AddObject", AddObject);
  ros::ServiceServer srv_check = n.advertiseService("evarobot_competition/CheckObject", CheckObject);
  ros::ServiceServer srv_start = n.advertiseService("evarobot_competition/Start", Start);
  
  ros::Subscriber sub_odom = n.subscribe("odom", 2, CallbackOdom);
  
  
  ros::Rate loop_rate(100.0);
  
  while(!start_flag)
  {
		ros::spinOnce();
    loop_rate.sleep();
	}
	begin = ros::Time::now();
  ROS_INFO("----- START ------");

  while(ros::ok())
  {
		
		// Geçen Süreyi Kontrol et. Yarışma süresi dolduğu zaman raporu ekrana yazdır ve kapat.
		if(duration*60.0 - (ros::Time::now() - begin).toSec() <= 0)
		{
			ROS_INFO("----- TIME IS UP ------");
			printReport();
			return 0;
		}
		
		if(objects.size() > 0 && myreport.size() == objects.size())
		{
			ROS_INFO("----- ALL OBJECTS WERE FOUNDED ------");
			printReport();
			return 0;
		}
		
		ros::spinOnce();
    loop_rate.sleep();
	}
	printReport();
  return 0;
}

