#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>
#include <climits>

#include "AdjacencyMatrix.hpp"

class Dijkstra {
    private:
        static int MinDistance(int numVerts, int dist[], bool visited[]);
        static std::vector<int> ReverseLookupPath(int parent[], int src, int dest);
    public:
        static std::vector<int> ShortestPath(int numVerts, AdjacencyMatrix *adjMat, int src, int dest);
};

#endif // DIJKSTRA_H