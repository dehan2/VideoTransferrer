#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "video_transferrer/ImageConverter.h"

using namespace std;


int main(int argc, char** argv)
{
    ros::init(argc, argv, "compressed_video_receiver_node");
    ros::NodeHandle n;

    cout << "OpenCV Version : " << CV_VERSION << endl;
    cv::namedWindow("EXAMPLE01", cv::WINDOW_AUTOSIZE);

    ImageConverter converter;
    ros::Subscriber sub = n.subscribe("/cam1/compressed_image", 10, &ImageConverter::compressed_image_message_callback, &converter);

    cv::Mat img;
    while (ros::ok())
	{
        ros::spinOnce();
		img = converter.get_image();
        if(img.rows > 0 && img.cols > 0)
        {
            cv::Mat greyImg = cv::Mat::zeros(img.rows, img.cols, CV_8U);
            for(int i=0; i<img.rows; i++)
            {
                for(int j=0; j<img.cols; j++)
                {
                    unsigned char r = img.at<cv::Vec3b>(i,j)[0];
                    unsigned char g = img.at<cv::Vec3b>(i,j)[1];
                    unsigned char b = img.at<cv::Vec3b>(i,j)[2];
                    unsigned char grey = 0.21 * r + 0.72 * g + 0.07 * b;
                    greyImg.at<uchar>(i, j) = grey;
                }
            }

            cv::imshow("EXAMPLE01", greyImg);

            if (cv::waitKey(1) == 27)
                break;
        }
	}
    
    return 0;
}