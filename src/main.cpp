#include <iostream>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "MapNavigator.hpp"

const std::string APP_TITLE = "Campus Path Planner";

cv::Point *start, *finish;
cv::Mat mapImg, outlineImg;
MapNavigator *navigator;

// Used to scale down the input outline image by the given resize factor
// We do this due to the speed and memory constraints of trying to store
// the entire image graph as an adjacency matrix
const int RESIZE_FACTOR = 6;

// Generates a new map with the starting and ending points drawn, if applicable
void DrawStartFinishPoints() {
    cv::Mat drawnMap = mapImg.clone();
    const int COORD_RADIUS = 3;

    if (start != NULL)
        cv::circle(drawnMap, *start, COORD_RADIUS, CV_RGB(255, 0, 0), cv::FILLED);

    if (finish != NULL)
        cv::circle(drawnMap, *finish, COORD_RADIUS, CV_RGB(0, 0, 255), cv::FILLED);

    cv::imshow(APP_TITLE, drawnMap);
    drawnMap.release();
}

// Handles the three mouse button clicks for editing the path planning
// parameters and for calculating the shortest path
void OnMouseEvent(int event, int x, int y, int flags, void* userdata) {
    switch (event) {
        case cv::EVENT_LBUTTONUP: {
            // Check that the start coordinate sits on a navigable path
            if (outlineImg.at<uchar>(y, x) == 0) {
                std::cout << "ALERT: Starting point is not on a navigable path! Aborting path planning..." << std::endl;
                return;
            }

            if (start != NULL)
                delete start;
            start = new cv::Point(x, y);

            std::cout << "Starting point set at (" << start->x << ", " << start->y << ")" << std::endl;
            DrawStartFinishPoints();
            break;
        }
        case cv::EVENT_RBUTTONUP: {
            // Check that the end coordinate sits on a navigable path
            if (outlineImg.at<uchar>(y, x) == 0) {
                std::cout << "ALERT: Ending point is not on a navigable path! Aborting path planning..." << std::endl;
                return;
            }

            if (finish != NULL)
                delete finish;
            finish = new cv::Point(x, y);

            std::cout << "Ending point set at (" << finish->x << ", " << finish->y << ")" << std::endl;
            DrawStartFinishPoints();
            break;
        }
        case cv::EVENT_MBUTTONUP: {
            // Check that both start and end coordinates have been assigned
            if (start == NULL) {
                std::cout << "ALERT: Starting point is not set! Aborting path planning..." << std::endl;
                return;
            }

            if (finish == NULL) {
                std::cout << "ALERT: Ending point is not set! Aborting path planning..." << std::endl;
                return;
            }

            // Calculate the shortest path
            std::cout << "Calculating path...";
            std::vector<cv::Point> shortestPath = navigator->CalculatePath(*start, *finish, RESIZE_FACTOR);
            std::cout << "done!" << std::endl;

            // Draw the computed path on the same map
            cv::Mat drawnMap = navigator->DrawPath(mapImg, shortestPath);
            cv::imshow(APP_TITLE, drawnMap);
            drawnMap.release();
            break;
        } // default: we ignore the unimportant mouse events
    }
}

// Create a basic image GUI display with a title, the
// intial image, and a mouse event listener callback
void CreateImageDisplay(
    const std::string &title, const cv::Mat &image,
    void (*OnMouseEvent) (int, int, int, int, void*)
) {
    cv::namedWindow(title);
    cv::setMouseCallback(title, OnMouseEvent);
    cv::imshow(title, image);
}

// Halt the program until the user has pressed 'Enter'
void WaitForReturn() {
    std::cout << '\n' << "Press Enter to continue...";
    std::cin.ignore();
}

// Prints out the instructions for using this program and waits for the user to proceed
void FirstContactGreeting() {
    std::cout << "DVC Campus Navigator Project!" << std::endl;
    std::cout << std::endl;
    std::cout << "Instructions:" << std::endl;
    std::cout << "  - Left click: Set start point" << std::endl;
    std::cout << "  - Right click: Set end point" << std::endl;
    std::cout << "  - Middle click: Plot the shortest path" << std::endl;
    std::cout << "Press any key on your keyboard to quit!" << std::endl;

    WaitForReturn();
}

int main(int argc, char const *argv[]) {
    // Greet the user with some instructions for using this program
    FirstContactGreeting();

    // Read both the original map and the outline map, if possible
    mapImg = cv::imread("data/map.png", CV_LOAD_IMAGE_COLOR);
    if (mapImg.empty()) {
        std::cout << "Error loading map image! Aborting..." << std::endl;
        return -1;
    }

    outlineImg = cv::imread("data/outline.png", CV_LOAD_IMAGE_GRAYSCALE);
    if (outlineImg.empty()) {
        std::cout << "Error loading outline image! Aborting..." << std::endl;
        return -1;
    }

    std::cout << "Initializing map navigator...";

    cv::Mat outlineImgClone;
    cv::resize(outlineImg, outlineImgClone, cv::Size(outlineImg.cols / RESIZE_FACTOR, outlineImg.rows / RESIZE_FACTOR));

    navigator = new MapNavigator(outlineImgClone);
    std::cout << "done!" << std::endl;

    // Create and run GUI program until user presses any key to quit
    CreateImageDisplay(APP_TITLE, mapImg, OnMouseEvent);
    cv::waitKey(0);

    // Clean up after ourselves
    delete navigator;
    delete start;
    delete finish;

    mapImg.release();
    outlineImg.release();

    return 0;
}