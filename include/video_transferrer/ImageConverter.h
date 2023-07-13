#pragma once

#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <sensor_msgs/CompressedImage.h>

class ImageConverter
{
private:
    cv::Mat m_image;

public:
    ImageConverter() = default;
    ~ImageConverter() = default;

    const cv::Mat& get_image() const {return m_image;}

    void image_message_callback(const sensor_msgs::Image::ConstPtr& msg);
    void compressed_image_message_callback(const sensor_msgs::CompressedImage::ConstPtr& msg);

    sensor_msgs::Image convert_cv_image_into_ros_message(const cv::Mat& inputImage, const int& counter = 0) const;
    sensor_msgs::CompressedImage convert_cv_image_into_compressed_ros_message(const cv::Mat& inputImage, const int& counter = 0) const;
};
