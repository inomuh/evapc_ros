#include "ros/ros.h"
#include "tf/transform_broadcaster.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/PoseWithCovarianceStamped.h"


geometry_msgs::TransformStamped odom_trans;
geometry_msgs::TransformStamped combined_odom_trans;


void Callback(const nav_msgs::Odometry::ConstPtr& msg)
{
    odom_trans.header.stamp = msg->header.stamp;//ros::Time::now();
    odom_trans.header.frame_id = msg->header.frame_id;
    odom_trans.child_frame_id = msg->child_frame_id;

    odom_trans.transform.translation.x = msg->pose.pose.position.x;
    odom_trans.transform.translation.y = msg->pose.pose.position.y;
    odom_trans.transform.translation.z = msg->pose.pose.position.z;
    odom_trans.transform.rotation = msg->pose.pose.orientation;
	
}

void CallbackCombined(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg)
{
    combined_odom_trans.header.stamp = ros::Time::now();
    combined_odom_trans.header.frame_id = "odom_combined";
    combined_odom_trans.child_frame_id = "base_link";

    combined_odom_trans.transform.translation.x = msg->pose.pose.position.x;
    combined_odom_trans.transform.translation.y = msg->pose.pose.position.y;
    combined_odom_trans.transform.translation.z = msg->pose.pose.position.z;
    combined_odom_trans.transform.rotation = msg->pose.pose.orientation;
	
}

int main(int argc, char** argv){
  ros::init(argc, argv, "odom_to_base");

  ros::NodeHandle n;
 // ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("odom", 50);
  ros::Subscriber sub_odom = n.subscribe("odom", 1, Callback);
  ros::Subscriber sub_odom_combined = n.subscribe("robot_pose_ekf/odom_combined", 1, CallbackCombined);
  
  tf::TransformBroadcaster odom_broadcaster;
	tf::TransformBroadcaster combined_odom_broadcaster;
  ros::Rate r(100);
  
  while(n.ok())
  {

	// check for incoming messages
    ros::spinOnce();               
    
    //send the transform
    odom_broadcaster.sendTransform(odom_trans);
//   combined_odom_broadcaster.sendTransform(combined_odom_trans);
		
   r.sleep();
  }
}
