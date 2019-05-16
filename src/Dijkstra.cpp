#include "Dijkstra.hpp"

// find the node with the smallest distance that's not visited
int Dijkstra::MinDistance(int numVerts, int dist[], bool visited[]) {
    int minDist = INT_MAX, closestPixel;

    // for each and every node (a.k.a pixel) in the graph
    for (int pixelLoc = 0; pixelLoc < numVerts; pixelLoc++)
        if (!visited[pixelLoc] && dist[pixelLoc] <= minDist)
            minDist = dist[pixelLoc], closestPixel = pixelLoc;

    return closestPixel;
}

// Get the path of pixel coordinates as a std::vector
std::vector<int> Dijkstra::ReverseLookupPath(int parent[], int src, int dest) {
    std::vector<int> path;

    int pixelLoc = dest;
    while (parent[pixelLoc] != -1) {
        path.push_back(pixelLoc);
        pixelLoc = parent[pixelLoc];
    }

    path.push_back(src);

    return path;
}

std::vector<int> Dijkstra::ShortestPath(int numVerts, AdjacencyMatrix *adjMat, int src, int dest) {
    unsigned char **graph = adjMat->GetAdjMatrixPointer();
    int dist[numVerts];         // used to keep track of cummulative distance from one point to the next
    bool visited[numVerts];     // used to keep track of already processed nodes
    int parent[numVerts];       // a reverse look-up array used to keep track of the paths by assigning parent[i + 1] = i, where i is a node index

    for (int i = 0; i < numVerts; i++) {
        parent[i] = -1;
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    // Source node always has distance of zero
    dist[src] = 0;

    for (int count = 0; count < (numVerts - 1); count++) {
        int closestPixel = Dijkstra::MinDistance(numVerts, dist, visited);

        // if u refers to the target node, then we are done here
        if (closestPixel == dest)
            break;

        visited[closestPixel] = true;

        // for each and every node (a.k.a pixel) in the graph
        for (int otherPixel = 0; otherPixel < numVerts; otherPixel++) {
            int edgeWeight = graph[closestPixel][otherPixel];
            if (
                !visited[otherPixel] &&
                edgeWeight != 0 &&
                (dist[closestPixel] + edgeWeight) < dist[otherPixel]
            ) {
                parent[otherPixel] = closestPixel;
                dist[otherPixel] = dist[closestPixel] + edgeWeight;
            }
        }
    }

    return Dijkstra::ReverseLookupPath(parent, src, dest);
}