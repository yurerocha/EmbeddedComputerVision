#ifndef QRCODE_H
#define QRCODE_H

#include <opencv2/aruco.hpp>
#include <vector>
#include <string>
#include "Detectable.h"
#include "Util.h"

class QRCode : public Detectable {
public:
    QRCode();
    ~QRCode();

    void detectObject(const cv::Mat& inputImage) override;
    void drawContour(cv::Mat& outputImage) override;
    std::tuple<bool, cv::Point2f> getCoordinates(int objectID) override;
    std::vector<std::tuple<int, cv::Point2f>>* getAllCoordinates() override;

private:
    std::vector<int> _markerIds;
    std::vector<std::vector<cv::Point2f>> _markerCorners;
    cv::Ptr<cv::aruco::Dictionary> _dictionary;
    std::vector<std::tuple<int, cv::Point2f>> _mainCorner;
};

#endif