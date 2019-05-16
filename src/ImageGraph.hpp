#ifndef IMG_GRAPH_H
#define IMG_GRAPH_H

#include <vector>
#include <climits>
#include <opencv2/core/core.hpp>

#include "AdjacencyMatrix.hpp"
#include "Dijkstra.hpp"

const cv::Point NB_UPLEFT = cv::Point(-1, -1);
const cv::Point NB_UP = cv::Point(-1, 0);
const cv::Point NB_UPRIGHT = cv::Point(-1, 1);

const cv::Point NB_LEFT = cv::Point(0, -1);
const cv::Point NB_RIGHT = cv::Point(0, 1);

const cv::Point NB_DOWNLEFT = cv::Point(1, -1);
const cv::Point NB_DOWN = cv::Point(1, 0);
const cv::Point NB_DOWNRIGHT = cv::Point(1, 1);

const int MAX_NEIGHBORS = 8;
const cv::Point ALL_NEIGHBORS[8] = {
    NB_UPLEFT, NB_UPRIGHT, NB_DOWNLEFT, NB_DOWNRIGHT,
    NB_UP, NB_LEFT, NB_RIGHT, NB_DOWN
};

// A graph-based data structure for representing an image as a graph, with each pixel representing
// a node and any two neighboring white pixel representing as edges.

class ImageGraph {
    private:
        cv::Mat img;
        AdjacencyMatrix *adjMat;
        int rows, cols;

        std::vector<cv::Point> GenerateNeighbors(int x, int y);
        int PointToIndex(int x, int y) const { return y * rows + x; };
        int PointToIndex(cv::Point pt) const { return pt.y * rows + pt.x; };
        cv::Point IndexToPoint(int index) const { return cv::Point(index % rows, index / rows); }

    public:
        ImageGraph(cv::Mat outlineImg);
        ~ImageGraph() { delete adjMat; };

        std::vector<cv::Point> ShortestPath(cv::Point start, cv::Point finish);
};

#endif // IMG_GRAPH_H