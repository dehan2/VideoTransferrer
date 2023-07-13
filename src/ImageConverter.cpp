#include "video_transferrer/ImageConverter.h"
#include <iostream>

using namespace std;

void ImageConverter::image_message_callback(const sensor_msgs::Image::ConstPtr& msg)
{
    cv_bridge::CvImagePtr cv_ptr;
    try
    {
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::RGB8);
    }
    catch(cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }

    m_image = cv_ptr->image;
}



void ImageConverter::compressed_image_message_callback(const sensor_msgs::CompressedImage::ConstPtr& msg)
{
    cv_bridge::CvImagePtr cv_ptr;
    try
    {
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::RGB8);
    }
    catch(cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }

    m_image = cv_ptr->image;
}



sensor_msgs::Image ImageConverter::convert_cv_image_into_ros_message(const cv::Mat& inputImage, const int& counter) const
{
    std_msgs::Header header;
    header.seq = counter;
    header.stamp = ros::Time::now();

    cv_bridge::CvImage imageBridge(header, sensor_msgs::image_encodings::RGB8, inputImage);
    
    sensor_msgs::Image message;
    imageBridge.toImageMsg(message);
    return message;
}



sensor_msgs::CompressedImage ImageConverter::convert_cv_image_into_compressed_ros_message(const cv::Mat& inputImage, const int& counter) const
{
    std_msgs::Header header;
    header.seq = counter;
    header.stamp = ros::Time::now();

    cv_bridge::CvImage imageBridge(header, sensor_msgs::image_encodings::RGB8, inputImage);
    
    sensor_msgs::CompressedImage message;
    imageBridge.toCompressedImageMsg(message);
    return message;
}