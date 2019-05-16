#include "ImageGraph.hpp"

// Initialize the graph with all the pixels as nodes
// and all neighboring white pixel pairs as edges
ImageGraph::ImageGraph(cv::Mat outlineImg) {
    img = outlineImg.clone();
    rows = img.rows;
    cols = img.cols;

    // Generate adjacency matrix
    this->adjMat = new AdjacencyMatrix(rows * cols);
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (img.at<uchar>(r, c)) {
                std::vector<cv::Point> neighbors = this->GenerateNeighbors(c, r);

                for (cv::Point neighbor : neighbors) {
                    int origIndex = this->PointToIndex(c, r);
                    int neighborIndex = this->PointToIndex(neighbor);
                    this->adjMat->AddEdge(origIndex, neighborIndex);
                }
            }
        }
    }
}

std::vector<cv::Point> ImageGraph::GenerateNeighbors(int x, int y) {
    std::vector<cv::Point> neighbors;

    for (cv::Point neighbor : ALL_NEIGHBORS) {
        int c = x + neighbor.x;
        int r = y + neighbor.y;

        // exclude neighbors that are out of range of the original image
        if (c >= cols or r >= rows)
            continue;
        if (c < 0 or r < 0)
            continue;

        // add only neighbors that are part of a valid path
        if (img.at<uchar>(r, c) == 255)
            neighbors.push_back(cv::Point(c, r));
    }

    return neighbors;
}

std::vector<cv::Point> ImageGraph::ShortestPath(cv::Point start, cv::Point finish) {
    int startIndex = this->PointToIndex(start);
    int finishIndex = this->PointToIndex(finish);

    std::vector<int> indexPath = Dijkstra::ShortestPath(rows * cols, adjMat, startIndex, finishIndex);

    std::vector<cv::Point> pointPath;
    for (int indexNode : indexPath) {
        cv::Point pointNode = this->IndexToPoint(indexNode);

        // insert points into the path in reverse order, since it's already reversed
        pointPath.insert(pointPath.begin(), pointNode);
    }

    return pointPath;
}