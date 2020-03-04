#include "ros/ros.h"
#include "protocol_msgs/Packet.h"

#include <iostream>
#include <inttypes.h>

using namespace std;

ros::Publisher pub;

int32_t addressHigh;
int32_t addressLow;

void packetReceived(const protocol_msgs::Packet::ConstPtr &packet)
{
    packet.addressHigh = addressHigh;
    packet.addressLow = addressLow;

    pub.publish(packet);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv);
    ros::NodeHandle nodeHandle;

    if (nodeHandle.getParam("addressHigh", addressHigh) == false) {
        ROS_FATAL("Parameter addressHigh not set.");
        return -1;
    }

    if (nodeHandle.getParam("addressLow", addressLow) == false) {
        ROS_FATAL("Parameter addressLow not set.")
        return -1;
    }

    pub = nodeHandle.advertise<protocol_msgs::Packet>("addressed_packet", 5);

    ros::Subscriber sub = nodeHandle.subscribe("packet", 1, packetReceived);

    ros::spin();

    return 0;
}