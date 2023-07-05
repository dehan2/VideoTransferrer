#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "video_transferrer/ImageConverter.h"

using namespace std;


int main(int argc, char** argv)
{
    ros::init(argc, argv, "video_sender_node");
    ros::NodeHandle n;
 
    cout << "OpenCV Version : " << CV_VERSION << endl;
    cv::namedWindow("EXAMPLE01", cv::WINDOW_AUTOSIZE);

    cv::VideoCapture cap(0);

    if(!cap.isOpened())
    {
        printf("Can't open the camera");
        return -1;
    }
    
    int counter = 0;
    ImageConverter converter;

    ros::Publisher pub = n.advertise<sensor_msgs::Image>("/cam1/image", 10);

    cv::Mat img;
    while (1)
	{
		cap >> img;
        sensor_msgs::Image imageMessage;
        imageMessage = converter.convert_cv_image_into_ros_message(img, counter++);
        pub.publish(imageMessage);
        ros::spinOnce();
	}

    return 0;
}