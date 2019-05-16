#include "MapNavigator.hpp"

// Calculate the shortest path via Dijkstra's algorithm
std::vector<cv::Point> MapNavigator::CalculatePath(cv::Point start, cv::Point finish, int resizeFactor) {
    // "shrink" the start and end points relative to the size of the outline image based on the resize factor
    cv::Point relocatedStart = cv::Point(start.x / resizeFactor, start.y / resizeFactor);
    cv::Point reolcatedFinish = cv::Point(finish.x / resizeFactor, finish.y / resizeFactor);

    std::vector<cv::Point> shortestPath = this->imgGraph->ShortestPath(relocatedStart, reolcatedFinish);

    // "expand" all points on the path to match the size of the original image
    for (cv::Point &point : shortestPath) {
        point.x *= resizeFactor;
        point.y *= resizeFactor;
    }

    return shortestPath;
}

// Draws a colored path from start to finish with the given path object and the original map image
cv::Mat MapNavigator::DrawPath(cv::Mat mapImg, std::vector<cv::Point> path) {
    cv::Mat mapImgCopy = mapImg.clone();
    const int COORD_RADIUS = 4;
    const int LINE_THICKNESS = 2;

    // Draw all the points in the path as green
    for (cv::Point coord : path) {
        cv::circle(mapImgCopy, coord, COORD_RADIUS - 1, cv::Scalar(0, 255, 0), cv::FILLED);
    }

    // Draw the starting point as red
    cv::Point start = path.front();
    cv::circle(mapImgCopy, start, COORD_RADIUS, CV_RGB(255, 0, 0), cv::FILLED);

    // Draw the ending point as blue
    cv::Point finish = path.back();
    cv::circle(mapImgCopy, finish, COORD_RADIUS, CV_RGB(0, 0, 255), cv::FILLED);

    return mapImgCopy;
}