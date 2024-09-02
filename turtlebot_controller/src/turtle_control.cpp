#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/TeleportAbsolute.h"

class TurtleController {
public:
    TurtleController() {
        // Initialize publisher for turtle's velocity
        pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);

        // Initialize client for teleport_absolute service
        teleport_client = nh.serviceClient<turtlesim::TeleportAbsolute>("/turtle1/teleport_absolute");
    }

    void teleportToStart() {
        turtlesim::TeleportAbsolute srv;
        srv.request.x = 1.0;   // Ensure within bounds
        srv.request.y = 1.0;   // Ensure within bounds
        srv.request.theta = 0.0;
        if (teleport_client.call(srv)) {
            ROS_INFO("Teleported turtle to start position");
        } else {
            ROS_ERROR("Failed to call service teleport_absolute");
        }
    }

    void moveSquare() {
        geometry_msgs::Twist move_cmd;
        
        ros::Rate rate(10); // 10 Hz update rate
        ros::Duration move_duration(2.0); // Adjust as needed based on speed
        ros::Duration turn_duration(1.5); // Adjust as needed for 90 degree turns

        for (int i = 0; i < 4; ++i) {
              // Move forward
        move_cmd.linear.x = 9.0; // Adjust speed as needed
        move_cmd.angular.z = 0.0;
        pub.publish(move_cmd);
        rate.sleep();
        ros::Duration(2.0).sleep(); // Move for 2 seconds

        // Turn 90 degrees
        move_cmd.linear.x = 0.0;
        move_cmd.angular.z = 1.56; // Adjust turning speed as needed
        pub.publish(move_cmd);
        rate.sleep();
        ros::Duration(1.5).sleep(); // Turn for 1.5 seconds

        // Stop turning
        move_cmd.angular.z = 0.0;
        pub.publish(move_cmd);
        rate.sleep();

        }

        // Stop moving
        move_cmd.linear.x = 0.0;
        move_cmd.angular.z = 0.0;
        pub.publish(move_cmd);
    }
    
      void moveInTriangle()
    {
        geometry_msgs::Twist move_cmd;
    ros::Rate rate(10); // 10 Hz update rate

    // Define the duration for moving forward and turning
    ros::Duration move_duration(2.0); // Adjust as needed based on speed
    ros::Duration turn_duration(1.5); // Adjust as needed for 120 degree turns

    // Move in a triangle
    for (int i = 0; i < 1; ++i) {
              // Move forward
        move_cmd.linear.x = 9.0; // Adjust speed as needed
        move_cmd.angular.z = 0.0;
        pub.publish(move_cmd);
        rate.sleep();
        ros::Duration(2.0).sleep(); // Move for 2 seconds

        // Turn 90 degrees
        move_cmd.linear.x = 0.0;
        move_cmd.angular.z = 1.56; // Adjust turning speed as needed
        pub.publish(move_cmd);
        rate.sleep();
        ros::Duration(1.5).sleep(); // Turn for 1.5 seconds

        // Stop turning
        move_cmd.angular.z = 0.0;
        pub.publish(move_cmd);
        rate.sleep();

        }
        // Move forward
        move_cmd.linear.x = 9.0; // Adjust speed as needed
        move_cmd.angular.z = 0.0;
        pub.publish(move_cmd);
        rate.sleep();
        ros::Duration(2.0).sleep(); // Move for 2 seconds

        // Turn 120 degrees
        move_cmd.linear.x = 0.0;
        move_cmd.angular.z = 2.33; // Adjust turning speed as needed
        pub.publish(move_cmd);
        rate.sleep();
        ros::Duration(1.5).sleep(); // Turn for 1.5 seconds

        // Stop turning
        move_cmd.angular.z = 0.0;
        pub.publish(move_cmd);
        rate.sleep();
        
        // Move forward
        move_cmd.linear.x = 13.0; // Adjust speed as needed
        move_cmd.angular.z = 0.0;
        pub.publish(move_cmd);
        rate.sleep();
        ros::Duration(2.0).sleep(); // Move for 2 seconds
    

    // Stop moving
    move_cmd.linear.x = 0.0;
    move_cmd.angular.z = 0.0;
    pub.publish(move_cmd);
 
    }


private:
    ros::NodeHandle nh;
    ros::Publisher pub;
    ros::ServiceClient teleport_client;
};

int main(int argc, char **argv) {
    ros::init(argc, argv, "turtle_control");
    TurtleController controller;
    controller.teleportToStart();
    ros::Duration(2).sleep();  // Wait for teleportation to complete
    controller.moveSquare();
    ros::Duration(2).sleep();  // Wait for teleportation to complete
    controller.moveInTriangle();
    ros::spin();
    return 0;
}

