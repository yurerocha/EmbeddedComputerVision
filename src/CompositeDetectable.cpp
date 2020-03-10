#include "CompositeDetectable.h"

CompositeDetectable::~CompositeDetectable()
{
    for(Detectable* object : _detectedObjects)
        delete object;
}

void CompositeDetectable::detectObject(const cv::Mat& inputImage)
{
    for(auto object: _detectedObjects) {
        object->detectObject(inputImage);
    }
}

void CompositeDetectable::drawContour(cv::Mat& outputImage)
{
    for(auto object: _detectedObjects) {
        object->drawContour(outputImage);
    }
}

std::tuple<bool, cv::Point2f> CompositeDetectable::getCoordinates(int objectId)
{
    cv::Point2f point;
    bool found;

    for(auto object: _detectedObjects) {
        std::tie(found, point) = object->getCoordinates(objectId);
        if(found)
            return std::make_pair(found, point);
    }

    return std::make_pair(false, cv::Point2f(0.0, 0.0));
}

std::vector<std::tuple<int, cv::Point2f>>* CompositeDetectable::getAllCoordinates()
{
    _allCoordinates.clear();
    std::vector<std::tuple<int, cv::Point2f>>* auxiliar;

    for(auto object : _detectedObjects) {
        auxiliar = object->getAllCoordinates();
        _allCoordinates.insert(_allCoordinates.end(), auxiliar->begin(), auxiliar->end());
    }

    #if DEBUGGING_LEVEL == 2
        for(auto object : _allCoordinates)
            std::cout << "(" << std::get<0>(object) << ", " << std::get<1>(object) << ")" << std::endl;
    #endif

    return &_allCoordinates;
}

void CompositeDetectable::addObject(Detectable* object)
{
    _detectedObjects.push_back(object);
}

void CompositeDetectable::removeObject(const Detectable& object)
{

}
