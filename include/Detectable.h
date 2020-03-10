#ifndef DETECTABLE_H
#define DETECTABLE_H

#include <string>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core/types.hpp>
#include <tuple>
#include <vector>

class Detectable {
public:
    virtual ~Detectable() {};

    virtual void detectObject(const cv::Mat& inputImage) = 0;
    virtual void drawContour(cv::Mat& outputImage) = 0;
    virtual std::tuple<bool, cv::Point2f> getCoordinates(int objectId) = 0;
    virtual std::vector<std::tuple<int, cv::Point2f>>* getAllCoordinates() = 0;

private:
    std::string _name;
};

#endif