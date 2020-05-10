#include <iostream>
#include "ros/ros.h"
#include <gazebo_msgs/ModelState.h>

geometry_msgs::Pose global_pose_sonde;
double velocity = 0.01;

void setSondePose(int i, gazebo_msgs::ModelState& pose_sonde){
    pose_sonde.model_name = "unit_box";
    pose_sonde.pose.position.x = 0;
    pose_sonde.pose.position.y = 0;
    pose_sonde.pose.position.z = global_pose_sonde.position.z + velocity*i;
    std::cout<<pose_sonde.pose.position.z<<std::endl;

    pose_sonde.pose.orientation.x = 0;
    pose_sonde.pose.orientation.y = 0;
    pose_sonde.pose.orientation.z = 0;
    pose_sonde.pose.orientation.w = 1;

    pose_sonde.twist.angular.x = 0;
    pose_sonde.twist.angular.y = 0;
    pose_sonde.twist.angular.z = 0;

    pose_sonde.twist.linear.x = 0;
    pose_sonde.twist.linear.y = 0;
    pose_sonde.twist.linear.z = 0;


    //pose_sonde.reference_frame = 'world';


}

void sondePoseCallback(const gazebo_msgs::ModelStateConstPtr& msg){
    /*global_pose_sonde.position.x = msg->pose.position.x;
    global_pose_sonde.position.y = msg->pose.position.y;
    global_pose_sonde.position.z = msg->pose.position.z;
    std::cout<<msg->pose.position.x;*/

}

int main(int argc, char **argv){
	ros::init(argc, argv, "lower_sonde");
	ros::NodeHandle nh;

	// Publisher and Subsriber stuff
	ros::Publisher set_sonde_pose_pub = nh.advertise<gazebo_msgs::ModelState>("/gazebo/set_model_state", 1000);


    ros::Subscriber sub = nh.subscribe("/gazebo/model_state", 1000, sondePoseCallback);

	double dt = 0.01;
	int i =1;
    ros::Rate rate(20);
	//define the position of the sonde
	gazebo_msgs::ModelState pose_sonde;
	while(ros::ok()){

	    setSondePose(i, pose_sonde);
	    set_sonde_pose_pub.publish(pose_sonde);
	    std::cout<<i<<std::endl;

	    i++;

	    ros::spinOnce();
	    rate.sleep();
	}
	
	return 0;
}
