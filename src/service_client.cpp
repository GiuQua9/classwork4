#include "ros/ros.h"
#include "cwork4/tf_frame.h"

using namespace std;

int main(int argc, char **argv) {

	//Init the ROS node with service_client name
	ros::init(argc, argv, "pose_client");
	ros::NodeHandle n;

	ros::ServiceClient client = n.serviceClient<cwork4::tf_frame>("pose");
	
	cwork4::tf_frame srv;
	srv.request.frame_a = "/base_link";
	srv.request.frame_b  = "/camera_link";
	
	ROS_INFO("Waiting for the client server");
	client.waitForExistence();
	ROS_INFO("Client server up now");
	
	if (!client.call(srv)) {
		ROS_ERROR("Error calling the service");
		return 1;
	}

	//Just print the output
	cout << "Service output: " << srv.response.pose << endl;
	
	return 0;
}
