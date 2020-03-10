#include <opencv2/imgcodecs.hpp> // cv::imread()
#include <opencv2/highgui.hpp> // cv::namedWindow(), cv::imshow()
#include <opencv2/core/core.hpp>
#include <iostream>
#include <string>
#include "Detectable.h"
#include "QRCode.h"
#include "CompositeDetectable.h"
#include "Grid.h"

using namespace cv;

int main(int argc, char* argv[])
{
    if(argc != 2) {
        std::cout <<" Usage: ./run camera_identifier" << std::endl;
        return -1;
    }

    VideoCapture cap;
    cap.open(std::stoi(argv[1]));
    // check if we succeeded
    if (!cap.isOpened()) {
        std::cerr << "ERROR! Unable to open camera\n";
        return -1;
    }

    CompositeDetectable *detection = new CompositeDetectable();
    detection->addObject(new QRCode());
    Grid *grid = new Grid(detection);
    std::string gridName = "Grid";
    States state = States::doNothing;

    Mat frame;
    cv::namedWindow(gridName, cv::WINDOW_AUTOSIZE);// Create a window for display.
    int keystroke;
    while(true) {
        cap.read(frame);
        
        #if DEBUGGING_LEVEL > 0
            if (frame.empty()) {
                std::cerr << "ERROR! blank frame grabbed" << std::endl;;
                break;
            }
        #endif

        if(state == States::detect) {
            grid->getAllCoordinates();
            grid->mapToGrid();
        }
        else if(state == States::calibrate) {
            if(grid->calibrateGrid())
                state = States::detect;
        } 
        else if(state == States::leave)
            break;

        detection->detectObject(frame);
        #if DEBUGGING_LEVEL > 0
            detection->drawContour(frame);
        #endif

        // flip(frame, frame, 1);
        imshow(gridName, frame);
        keystroke = waitKey(10);
        
        switch(keystroke) {
        case 'c':
            state = States::calibrate;
            break;
        case 'q': // quit whether ESC or 'q' is entered
        case 27:
            state = States::leave;
            break;
        default:
            break;
        }
    }

    delete detection;
    delete grid;
    destroyAllWindows();
    cap.release();
    frame.release();

    return 0;
}