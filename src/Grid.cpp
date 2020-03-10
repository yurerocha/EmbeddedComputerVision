#include "Grid.h"

Grid::Grid(CompositeDetectable* composite) {
    _referenceMarkerIdOrigin = 0;
    _referenceMarkerId2 = 1;
    _referenceMarkerId3 = 2;
    _gridDimensionM = 5;
    _gridDimensionN = 7;

    _composite = composite;
    _allCoordinates = nullptr;
}

Grid::~Grid()
{
}

bool Grid::calibrateGrid()
{
    cv::Point2f point, anotherPoint;
    bool found;

    std::tie(found, point) = _composite->getCoordinates(_referenceMarkerIdOrigin);
    if(!found)
        return false;
    _referenceOrigin = point;

    std::tie(found, point) = _composite->getCoordinates(_referenceMarkerId2);
    if(!found)
        return false;

    std::tie(found, anotherPoint) = _composite->getCoordinates(_referenceMarkerId3);
    if(!found)
        return false;

    _referenceVector.x = std::max(point.x, anotherPoint.x);
    _referenceVector.y = std::max(point.y, anotherPoint.y);
    _referenceVector.x = abs(_referenceVector.x - _referenceOrigin.x);
    _referenceVector.y = abs(_referenceVector.y - _referenceOrigin.y);

    #if DEBUGGING_LEVEL == 1
        std::cout << "origin: (" << _referenceOrigin.x << ", " << _referenceOrigin.y << ")\t"
            <<  "reference vector: (" << _referenceVector.x << ", " << _referenceVector.y << ")" << std::endl;
    #endif

    return true;
}

void Grid::mapToGrid()
{
    cv::Point2i point;
    refreshGrid();

    for(int i = 0; i < _allCoordinates->size(); i++) {
        point = toGridCoordinates(std::get<1>((*_allCoordinates)[i]));
        if(point.x < 0 || point.x > _gridDimensionM)
            continue;
        if(point.y < 0 || point.y > _gridDimensionN)
            continue;
        _grid[point.y][point.x] = std::get<0>((*_allCoordinates)[i]); 
        // when mapped, y represents the row and x the column
    }

    #if DEBUGGING_LEVEL > 0
        printGrid();
    #endif
}

void Grid::getAllCoordinates()
{
   _allCoordinates = _composite->getAllCoordinates();
}

void Grid::printGrid()
{
    for(auto item : _grid) {
        for(int i : item)
            if(i == -1)
                std::cout << " ---";
            else
                std::cout << i << "---";
        std::cout << "\n|   |   |   |   |   |   |" << std::endl;
    }
}

void Grid::refreshGrid()
{
    _grid = std::vector<std::vector<int>>(_gridDimensionM, std::vector<int>(_gridDimensionN, -1));
}


cv::Point2i Grid::toGridCoordinates(cv::Point2f actualCoordinates)
{
    cv::Point2i gridCoordinates;

    // the rounding helps to pick up the right position of the objects in the physical grid
    gridCoordinates.x = round((actualCoordinates.x - _referenceOrigin.x) / (double)_referenceVector.x);
    gridCoordinates.y = round((actualCoordinates.y - _referenceOrigin.y) / (double)_referenceVector.y);

    return gridCoordinates;
}


