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
    protocol_msgs::Packet newPacket;
    newPacket.addressHigh = addressHigh;
    newPacket.addressLow = addressLow;

    newPacket.data = packet->data;

    pub.publish(newPacket);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "xbee_router");
    ros::NodeHandle nodeHandle;
    
    std::string paramHigh;
    if (ros::param::get("~addressHigh", paramHigh) == false) {
        ROS_FATAL("Parameter addressHigh not set.");
        return -1;
    }

    std::string paramLow;
    if (ros::param::get("~addressLow", paramLow) == false) {
        ROS_FATAL("Parameter addressLow not set.");
        return -1;
    }

    addressHigh = std::stoi(paramHigh, 0, 16);
    addressLow = std::stoi(paramLow, 0, 16);

    pub = nodeHandle.advertise<protocol_msgs::Packet>("addressed_packet", 5);

    ros::Subscriber sub = nodeHandle.subscribe("packet", 1, packetReceived);

    ros::spin();

    return 0;
}
