# hello-robotics
Lab 1
Laboratory Report 1

Introduction
	ROS is an open-source, meta-operating system used for robotics systems. It stands for Robotic Operating System.  This lab focused on exploring key ROS concepts, particularly the Publish/Subscribe and Service/Client communication models, using the turtlesim simulator. The exercises began with creating simple subscriber nodes to track the turtle's position, followed by implementing commands to control its movement. We also learned to interact with ROS services, allowing us to teleport the turtle and control its trajectory.
	By the end of the lab, we successfully programmed the turtle to move along predefined patterns, such as squares and triangles. This hands-on experience deepened our understanding of ROS, equipping us with essential skills for developing and debugging ROS-based robotic applications.

Task 1
The first task was to create two ROS nodes, a publisher and a subscriber, that communicate with each other. The publisher node was responsible for generating messages and publishing them to a specific topic, while the subscriber node listened to this topic and processed the received messages.
![Task 1](https://github.com/asemqr/hello-robotics/blob/images/task1.png)
Figure 1. Listener node

Task 2
The second task involved creating a ROS node that subscribes to the turtle1/pose topic in the turtlesim simulator and logs the turtle's position. This task aimed to deepen understanding of how to interact with ROS topics and how to interpret message structures.
We created a subscriber node called turtle_listener.cpp file in the src directory of a new ROS package, turtlebot_controller. We also used ROS commands (rostopic info and rosmsg show) to explore the structure and type of the messages published on the /turtle1/pose topic. The node was programmed to log the turtle's position whenever a new message was received(Fig.2).

![Task 2](https://github.com/asemqr/hello-robotics/blob/images/task2.png)
Figure 2. Turtle sim listener node output

Task 3
In task 3, we modified  turtle_listener.cpp to control the turtle’s movement. We first started ROS Master, roscore and then looked at the list of verbose topics through rostopic list –v, after which we identified the command to set the velocities of the turtle, /turtle1/cmd_vel.  A message of the type of geometry_msgs/Twist, is needed to publish to this topic, so we created twist message in the call back function that will be called every time a new message is publisedon turtle1/pose topic. There we set the linear.x and linear.y velocities, to 1, skipping linear.z as it is a planar simulator. Next, we published the Twist message to the /turtle1/cmd_vel topic.

To turn left or right, we also changed angular.z velocity. Since we already had a subscriber node that listened to the position of our turtle published by “turtle sim” node, we now needed to create a publisher node to send velocity commands using type <geometry_msgs::Twist>  and ("turtle1/cmd_vel", 1) parameters. 
After recompiling using catkin_make and running the node again we got the output described in Fig.3

![Task 3](https://github.com/asemqr/hello-robotics/blob/images/task3.png)
Figure 3. The turtle moving in circle

Task 4 Services
For RPC (remote Procedure Call) we need services instead of publish/subscriber architecture. After testing out few services in the list of rosservice list, we modified turtle_listener.cpp to use /spwn service.
Here we created a client for the /spawn service; defined the service message according to manual and made a function to call the service spawn for new turtles, using if statements (if (client1.call(srv1))->     ROS_INFO("Spawned turtle named %s at (%f, %f)", srv1.response.name.c_str(), srv1.request.x, srv1.request.y);
). There we added a few turtles as can be seen in Fig.4
![Task 1](https://github.com/asemqr/hello-robotics/blob/images/task4.png)
Figure 4. The spawned turtle

Task 5


