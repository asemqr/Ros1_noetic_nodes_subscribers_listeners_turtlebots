#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Spawn.h"

// Declare the publisher globally so it can be accessed in the callback function
ros::Publisher pub;

// Callback function that will be called every time a new message is published on /turtle1/pose
void poseCallback(const turtlesim::Pose::ConstPtr& msg)
{
    ROS_INFO("Turtle Position -> x: [%f], y: [%f], theta: [%f]", msg->x, msg->y, msg->theta);
    
    // Create a Twist message and set linear and angular velocities
    geometry_msgs::Twist my_vel;
    my_vel.linear.x = 1.0;
    my_vel.angular.z = 1.0;
    
    // Publish the Twist message to the /turtle1/cmd_vel topic
    pub.publish(my_vel); 
}

int main(int argc, char **argv)
{
    // Initialize the ROS system and become a node
    ros::init(argc, argv, "turtle_listener");
    ros::NodeHandle nh;
    
    // Define a publisher to the /turtle1/cmd_vel topic
    pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1);

    // Subscribe to the /turtle1/pose topic
    ros::Subscriber sub = nh.subscribe("turtle1/pose", 1000, poseCallback);

    ros::ServiceClient client1 = nh.serviceClient<turtlesim::Spawn>("/spawn");
    // Define the service message
    turtlesim::Spawn srv1;
    srv1.request.x = 1.0;             // X position for the new turtle
    srv1.request.y = 5.0;             // Y position for the new turtle
    srv1.request.theta = 0.0;         // Orientation of the new turtle
    srv1.request.name = "Turtle_junior"; // Name of the new turtle
   
    // Call the service to spawn the new turtle
    if (client1.call(srv1))
    {
        ROS_INFO("Spawned turtle named %s at (%f, %f)", srv1.response.name.c_str(), srv1.request.x, srv1.request.y);
    }
    else
    {
        ROS_ERROR("Failed to call service /spawn");
    }
    
    // Spin, so the program doesn't exit and keeps listening for messages
    ros::spin();

    return 0;
}


