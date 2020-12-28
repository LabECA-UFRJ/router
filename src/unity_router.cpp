#include "ros/ros.h"
#include "controller_msgs/MotorSignal.h"
#include "simulation_msgs/RobotWheelSpeed.h"

#include <iostream>
#include <inttypes.h>

using namespace std;

ros::Publisher pub;

int32_t robotId;

void twistReceived(const controller_msgs::MotorSignal::ConstPtr &motorSignal)
{
    simulation_msgs::RobotWheelSpeed robotWheel;

    robotWheel.id = robotId;
    robotWheel.left = motorSignal->leftMotor;
    robotWheel.right = motorSignal->rightMotor;

    pub.publish(robotWheel);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "unity_router");
    ros::NodeHandle nodeHandle;

    if (ros::param::get("~id", robotId) == false) {
        ROS_FATAL("Parameter id not set.");
        return -1;
    }

    pub = nodeHandle.advertise<simulation_msgs::RobotWheelSpeed>("robot_cmd_vel", 5);

    ros::Subscriber sub = nodeHandle.subscribe("motor_signal", 1, twistReceived);

    ros::spin();

    return 0;
}
