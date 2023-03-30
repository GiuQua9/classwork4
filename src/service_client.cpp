#include "ros/ros.h"

//Header of the service message. 
//	The service message belongs to the ros_service package
#include "ros_service/sum.h"

using namespace std;

int main(int argc, char **argv) {

	//Init the ROS node with service_client name
	ros::init(argc, argv, "service_client");
	ros::NodeHandle n;

	//Init the service client. Data to use for the service (the .srv file) and the name of the service
	ros::ServiceClient client = n.serviceClient<ros_service::sum>("sum");
	
	//Define and initialize the service data structure 
	//	This datastructure brings with it the input value (in the request fields) and the output values, in the response field
	ros_service::sum srv;
	srv.request.x.data = 3.0;
	srv.request.y.data = 10.0;
	
	//Wait that in the ROS network, the service sum is advertised
	//	If you call a service and the service has not been advertised, you will have back an error
	ROS_INFO("Waiting for the client server");
	client.waitForExistence();
	ROS_INFO("Client server up now");
	
	//Call the service callback
	//	The return value is false if:
	//		- the callback returns false
	//		- the service has not been found in the ROS network
	if (!client.call(srv)) {
		ROS_ERROR("Error calling the service");
		return 1;
	}

	//Just print the output
	cout << "Service output: " << srv.response.sum << endl;
	
	return 0;
}
