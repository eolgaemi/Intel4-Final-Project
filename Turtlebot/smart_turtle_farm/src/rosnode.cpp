/* kccistc embedded & iot by ksh */
#include "../include/smart_turtle_farm/rosnode.h"
//********************* */
//int socknum;
//int arcnum = 0;
//int objnum = 1;
//********************* */
RosNode::RosNode(int argc, char** argv)
{
    ros::init(argc, argv, "rosqt");

    if (!ros::master::check()) {
        return;
    }
    base_cmd.linear.x = 0.0;
    base_cmd.linear.y = 0.0;
    base_cmd.linear.z = 0.0;
    base_cmd.angular.x = 0.0;
    base_cmd.angular.y = 0.0;
    base_cmd.angular.z = 0.0;
    ros::NodeHandle nh;

    set_pub =
          nh.advertise<geometry_msgs::PoseWithCovarianceStamped>("initialpose", 100);
    goal_pub =
          nh.advertise<geometry_msgs::PoseStamped>("move_base_simple/goal", 100);
    cmd_vel_pub =
          nh.advertise<geometry_msgs::Twist>("cmd_vel", 1);
    lds_sub =
         nh.subscribe("scan", 100, &RosNode::LDSMsgCallback,this);
    image_sub =
         nh.subscribe("cv_camera/image_raw", 1, &RosNode::imageCallback,this);
//    ROS_INFO("%s", "create ros node");
    socknum;
    arcnum = 0;
    objnum = 1;
    socknum = connectToServer(); //yoon*************************
//    ros::start();
}

RosNode::~RosNode(){
    if(ros::isStarted()) {
      ros::shutdown(); // explicitly needed since we use ros::start();
      ros::waitForShutdown();
    }
    close(socknum);//yoon**************************
    wait();
}

void RosNode::run()
{
    ros::Rate loop_rate(20);    //20hz : 0.2Sec
    while(ros::ok())
    {
        if(baseCmdFlag)
        {
            cmd_vel_pub.publish(base_cmd);
        }
        ros::spinOnce();
        loop_rate.sleep();
    }
    emit rosShutdown();
}
void RosNode::set_goal(QString frame, double x, double y, double z, double w) {
  geometry_msgs::PoseStamped goal;
  ros::Rate loop_rate(10);

  goal.header.frame_id = frame.toStdString();

  goal.header.stamp = ros::Time::now();
  goal.pose.position.x = x;
  goal.pose.position.y = y;
  goal.pose.position.z = 0;
  goal.pose.orientation.z = z;
  goal.pose.orientation.w = w;

  set_pub.publish(goal);
}

void RosNode::go_goal(QString frame, double x, double y, double z, double w) {
  geometry_msgs::PoseStamped goal;

  goal.header.frame_id = frame.toStdString();

  goal.header.stamp = ros::Time::now();
  goal.pose.position.x = x;
  goal.pose.position.y = y;
  goal.pose.position.z = 0;
  goal.pose.orientation.z = z;
  goal.pose.orientation.w = w;

  goal_pub.publish(goal);

}

void RosNode::LDSMsgCallback(const sensor_msgs::LaserScan::ConstPtr &msg)
{

  float scanData[4];
  scanData[0] = msg->ranges[0];
  scanData[1] = msg->ranges[90];
  scanData[2] = msg->ranges[180];
  scanData[3] = msg->ranges[270];
//  qDebug() << "scanData[0] : " << scanData[0];
  emit sigLdsReceive(scanData);
}

void RosNode::set_cmd_vel(geometry_msgs::Twist baseCmd)
{
    base_cmd.linear.x = baseCmd.linear.x;
    base_cmd.angular.z = baseCmd.angular.z;
}

void RosNode::set_cmdBaseCmd(bool flag)
{
    baseCmdFlag = flag;
}

//***************************yoon code *************************************
int RosNode::connectToServer() {
    const char* SERVER_IP = "10.10.141.19"; // 서버 IP
    const int SERVER_PORT = 5000; // 서버 포트
    const int TIMEOUT = 30; // 타임아웃 시간 (초)

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        ROS_ERROR("Failed to create socket: %s", strerror(errno));
        return -1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        ROS_ERROR("Invalid address: %s", SERVER_IP);
        close(sock);
        return -1;
    }

    // 소켓에 타임아웃 설정
    struct timeval timeout;
    timeout.tv_sec = TIMEOUT;
    timeout.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (const char*)&timeout, sizeof(timeout));

    if (::connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        ROS_ERROR("Connection to server %s:%d failed: %s", SERVER_IP, SERVER_PORT, strerror(errno));
        close(sock);
        return -1;
    }

    return sock;
}

void RosNode::sendImageData(int sock, const cv::Mat& frame) {

    // 먼저 arcnum을 서버로 전송 (4바이트 int로 전송)
    int arcnum_net = htonl(arcnum);  // 네트워크 바이트 순서로 변환

    // arcnum 전송
    if (send(sock, reinterpret_cast<const char*>(&arcnum_net), sizeof(arcnum_net), 0) < 0) {
        ROS_ERROR("Failed to send arcnum: %s", strerror(errno));
        return;
    }

    std::vector<uchar> buffer;
    if (!cv::imencode(".jpg", frame, buffer)) {
        ROS_ERROR("Failed to encode image.");
        close(sock);
        return;
    }

    int data_size = buffer.size();
    data_size = htonl(data_size); // 네트워크 바이트 순서로 변환
    ROS_INFO("Sending image size: %d", ntohl(data_size)); // 전송하는 데이터 크기 로그

    // 데이터 크기 전송
    if (send(sock, reinterpret_cast<const char*>(&data_size), sizeof(data_size), 0) < 0) {
        ROS_ERROR("Failed to send data size: %s", strerror(errno));
        return;
    }

    // 이미지 데이터 전송
    if (send(sock, buffer.data(), buffer.size(), 0) < 0) {
        ROS_ERROR("Failed to send image data: %s", strerror(errno));
        return;
    }

}
void RosNode::receiveMessage(int sock) {
    // 메시지 크기 수신
    uint32_t message_length;
    int bytes_received = recv(sock, &message_length, sizeof(message_length), 0);
    
    if (bytes_received <= 0) {
        // 오류 처리 (0 또는 음수의 경우)
        ROS_WARN("Failed to receive message length.");
        return;
    }

    // 네트워크 바이트 순서에서 호스트 바이트 순서로 변환
    message_length = ntohl(message_length);

    // 실제 메시지 수신
    std::vector<char> buffer(message_length);
    bytes_received = recv(sock, buffer.data(), message_length, 0);

    if (bytes_received > 0) {
        std::string message(buffer.data(), bytes_received);
        ROS_INFO("Received message: %s", message.c_str());

        // 메시지가 "0"인 경우 arcnum을 0으로 설정
        if (message == "0") {
            objnum = 0; // arcnum 변수 설정
            ROS_INFO("objnum set to: %d", objnum);
        }
        else if (message == "1"){
           objnum = 1; // arcnum 변수 설정
          ROS_INFO("objnum set to: %d", objnum);
        }
        
        // 추가적인 메시지 처리 로직을 여기에 추가
    } 
    // bytes_received < 0인 경우는 무시하고 넘어감
}

void RosNode::imageCallback(const sensor_msgs::ImageConstPtr& msg)
{

    cv::Mat frame,cframe;
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);

    try
    {
        frame = cv_bridge::toCvShare(msg, "bgr8")->image;
    //    imwrite("cap.jpg",frame);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
    }
    cvtColor(frame, frame,  cv::COLOR_BGR2RGB);
    std::vector<int> ids;
    std::vector<std::vector<cv::Point2f>> corners;
    // ArUco 마커 감지
    cv::aruco::detectMarkers(frame, dictionary, corners, ids); //stf_pot1

    // 감지된 마커에 점 그리기
    if (!ids.empty()) {
        cv::aruco::drawDetectedMarkers(frame, corners, ids);

        for (size_t i = 0; i < corners.size(); i++) {
            // 각 마커의 ID를 상단에 텍스트로 출력
            std::string text = pots[ids[i]];

            cv::putText(frame, text,
                        corners[i][0], // 첫 번째 모서리 좌표 사용
                        cv::FONT_HERSHEY_SIMPLEX,
                        0.5, // 텍스트 크기
                        cv::Scalar(255, 0, 0), // 텍스트 색상 (파란색)
                        1, // 두께
                        cv::LINE_AA); // 선 스타일

            // 각 코너에 빨간색 점 그리기
            for (const auto& point : corners[i]) {
                cv::circle(frame, point, 5, cv::Scalar(0, 0, 255), -1); // 빨간색 점
            }
        }
        if(arcnum != ids[0] || objnum == 0){
            arcnum = ids[0];
            printf("find: %d\n",ids[0]);
            cvtColor(frame, cframe,  cv::COLOR_RGB2BGR);
            sendImageData(socknum, cframe);
            receiveMessage(socknum);
        }
    }

  cv::line(frame, cv::Point((frame.cols >> 1) - 20, frame.rows >> 1), cv::Point((frame.cols >> 1) + 20, frame.rows >> 1), cv::Scalar(255, 0, 0), 3);
  cv::line(frame, cv::Point(frame.cols >> 1, (frame.rows >> 1) - 20), cv::Point(frame.cols >> 1, (frame.rows >> 1) + 20), cv::Scalar(255, 0, 0), 3);
  QImage * pImage = new QImage(frame.data, frame.cols, frame.rows, QImage::Format_RGB888);
  QImage repImage = pImage->scaled( pLcamView->height(),pLcamView->width(), Qt::KeepAspectRatio);

  pLcamView->setPixmap(QPixmap::fromImage(repImage));
}
