#ifndef MAP_NAV_H
#define MAP_NAV_H

#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "ImageGraph.hpp"

// This class stores the map image as a graph and accepts
// starting/ending points for calculating an optimal route
class MapNavigator {
    private:
        ImageGraph *imgGraph;
    public:
        MapNavigator(cv::Mat outlineImg) { imgGraph = new ImageGraph(outlineImg); };
        ~MapNavigator() { delete imgGraph; };

        std::vector<cv::Point> CalculatePath(cv::Point start, cv::Point finish, int resizeFactor);
        cv::Mat DrawPath(cv::Mat mapImg, std::vector<cv::Point> path);
};

#endif // MAP_NAV_H