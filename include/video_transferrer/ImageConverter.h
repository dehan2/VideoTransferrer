#pragma once

#include <ros/ros.h>
//#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>

class ImageConverter
{
private:
    cv::Mat m_image;

public:
    ImageConverter() = default;
    ~ImageConverter() = default;

    const cv::Mat& get_image() const {return m_image;}

    void image_message_callback(const sensor_msgs::Image::ConstPtr& msg);

    sensor_msgs::Image convert_cv_image_into_ros_message(const cv::Mat& inputImage, const int& counter = 0) const;
};
