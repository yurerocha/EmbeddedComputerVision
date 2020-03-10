#include "QRCode.h"
#include <iostream>

QRCode::QRCode()
{
    // std::cout << "criado" << std::endl;
    _dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
}

QRCode::~QRCode ()
{
}

void QRCode::detectObject(const cv::Mat& inputImage) 
{
    // std::cout << _markerIds.size() << std::endl;
    cv::aruco::detectMarkers(inputImage, _dictionary, _markerCorners, _markerIds);
}

void QRCode::drawContour(cv::Mat& outputImage)
{
    // std::cout << _markerIds.size() << std::endl;
    if(_markerIds.size() > 0)
        cv::aruco::drawDetectedMarkers(outputImage, _markerCorners, _markerIds);
}

// return the first cv::Point2f of the first marker found in _markerCorners with objectId if objectId is a valid id; 
std::tuple<bool, cv::Point2f> QRCode::getCoordinates(int objectId)
{
    for(int i = 0; i < _markerIds.size(); i++) {
        if(objectId == _markerIds[i])
            return std::make_pair(true, _markerCorners[i][0]);
    }

    return std::make_pair(false, cv::Point2f(0.0, 0.0));
}

std::vector<std::tuple<int, cv::Point2f>>* QRCode::getAllCoordinates()
{
    _mainCorner = std::vector<std::tuple<int, cv::Point2f>>(_markerIds.size());

    for(int i = 0; i < _markerIds.size(); i++)
        _mainCorner[i] = std::make_pair(_markerIds[i], _markerCorners[i][0]);

    return &_mainCorner;
}
