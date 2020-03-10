#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <tuple>
#include "Util.h"
#include "CompositeDetectable.h"

class Grid {
public:
    Grid(CompositeDetectable *composite);
    ~Grid();

    bool calibrateGrid();
    void mapToGrid();
    void printGrid();
    void refreshGrid();

    void getAllCoordinates();
private:
    cv::Point2i toGridCoordinates(cv::Point2f actualCoordinates);

    cv::Point2f _referenceVector;
    cv::Point2f _referenceOrigin;

    CompositeDetectable* _composite;
    int _referenceMarkerIdOrigin, _referenceMarkerId2, _referenceMarkerId3;
    int _gridDimensionM, _gridDimensionN;
    std::vector<std::tuple<int, cv::Point2f>>* _allCoordinates;
    std::vector<std::vector<int>> _grid;
};

#endif