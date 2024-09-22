/* kccistc embedded & iot by ksh */
#ifndef __ROSNODE__H_
#define __ROSNODE__H_

#include <QThread>
#include <QSettings>
#include <QLabel>
#include <QDebug>
#include <sstream>
#include <string>

// ROS 관련 헤더
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/LaserScan.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/aruco.hpp>

// 소켓 프로그래밍 관련 헤더
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>  // close() 함수 사용을 위한 헤더
#include <cstring>   // memset() 함수 사용을 위한 헤더

class RosNode : public QThread{
    Q_OBJECT
public:
    RosNode(int argc, char **argv);
    ~RosNode();
    bool init();
    void run();
    void startHandle();
    void set_goal(QString frame, double x, double y, double z, double w);
    void go_goal(QString frame, double x, double y, double z, double w);
    void set_cmd_vel(geometry_msgs::Twist);
    void LDSMsgCallback(const sensor_msgs::LaserScan::ConstPtr &msg);
    void imageCallback(const sensor_msgs::ImageConstPtr& msg);
    void receiveMessage(int sock); //yoon

private:
    int init_argc;
    char **init_argv;
    QString goal_topic;
    geometry_msgs::Twist base_cmd;
    bool baseCmdFlag;
    ros::Publisher set_pub;
    ros::Publisher goal_pub;
    ros::Publisher cmd_vel_pub;
    ros::Subscriber lds_sub;

    ros::Subscriber image_sub;
    std::array<std::string, 4> pots = {"0","stf_pot1", "stf_pot2", "stf_pot3"}; //yoon
    int socknum;
    int arcnum;
    int objnum;

public:
    QLabel* pLcamView;
    void set_cmdBaseCmd(bool);
    //yoon
    void sendImage(const cv::Mat& frame);
    int connectToServer();
    void sendImageData(int sock, const cv::Mat& frame);
    int sock;
signals:
    void rosShutdown();
    void sigLdsReceive(float *);
};

#endif
