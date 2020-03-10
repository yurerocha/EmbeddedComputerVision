#ifndef COMPOSITE_DETECTABLE_H
#define COMPOSITE_DETECTABLE_H

#include <list>
#include <string>
#include <iterator>
#include <iostream>
#include "Detectable.h"
#include "Util.h"

class CompositeDetectable: public Detectable {
public:
    ~CompositeDetectable();

    void detectObject(const cv::Mat& inputImage) override;
    void drawContour(cv::Mat& outputImage) override;
    std::tuple<bool, cv::Point2f> getCoordinates(int objectId) override;
    std::vector<std::tuple<int, cv::Point2f>>* getAllCoordinates() override;

    void addObject(Detectable* object);
    void removeObject(const Detectable& object);

private:
    std::list<Detectable*> _detectedObjects;
    std::vector<std::tuple<int, cv::Point2f>> _allCoordinates;
};

#endif