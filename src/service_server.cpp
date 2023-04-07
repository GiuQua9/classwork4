#include "ros/ros.h"
#include "cwork4/tf_frame.h"
#include <tf/transform_listener.h>

using namespace std;

bool service_callback( cwork4::tf_frame::Request &req, cwork4::tf_frame::Response &res) {
	tf::TransformListener listener;
	tf::StampedTransform transform;
	try {
		listener.lookupTransform(req.frame_a, req.frame_b, ros::Time(0), transform);
	}
	catch (tf::TransformException ex){
		ROS_ERROR("%s",ex.what());
		ros::Duration(1.0).sleep();
	}


	return true;
}


int main(int argc, char **argv) {

	ros::init(argc, argv, "pose_service");
	ros::NodeHandle n;
	
	ros::ServiceServer service = n.advertiseService("pose", service_callback);

	//Call the spin function to maintain the node alive
	ros::spin();

	return 0;
}
