#include "ros/ros.h"
//Header of the service message. 
//	The service message belongs to the ros_service package
#include "ros_service/sum.h"

using namespace std;

//Callback function
//	Return value: boolean
//		If this function returns true, the service function has been corretly called
//		You can use this value to check if the function has been called with correct parameters
//		i.e. call a service calculating the square of a number, calling the service with a negative number
//	Input values:  the request part of the servive 
//				   the output of the service to fill
bool service_callback( ros_service::sum::Request &req, ros_service::sum::Response &res) {


	cout << "Service sum received: " << endl;
	//We know that the service is called with 2 parameters: x and y
	// These parameters are put in a data structure called req
	cout << req.x << req.y << endl;

	//The return value is store in the res datastrcutre
	cout << "Returning the sum" << endl;
	res.sum.data = req.x.data + req.y.data;

	return true;
}


int main(int argc, char **argv) {

	ros::init(argc, argv, "sum_service");
	ros::NodeHandle n;

	//Initialize the service object: name of the service and callback function
	//	Like subscribers, also tje callback function can be declared as a class function
	ros::ServiceServer service = n.advertiseService("sum", service_callback);

	//Call the spin function to maintain the node alive
	ros::spin();

	return 0;
}
