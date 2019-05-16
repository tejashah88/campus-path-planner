#include "AdjacencyMatrix.hpp"

AdjacencyMatrix::AdjacencyMatrix(int size) {
    this->size = size;
    this->adj = new unsigned char*[size];
    for (int i = 0; i < size; i++) {
        this->adj[i] = new unsigned char[size];
        for(int j = 0; j < size; j++)
            this->adj[i][j] = 0;
    }
}

AdjacencyMatrix::~AdjacencyMatrix() {
    for (int i = 0; i < size; i++)
        delete[] this->adj[i];
    delete[] this->adj;
}

bool AdjacencyMatrix::AddEdge(int origin, int dest, int weight) {
    if (origin > this->size || dest > this->size || origin < 0 || dest < 0)
        return false;
    else {
        this->adj[origin - 1][dest - 1] = weight;
        this->adj[dest - 1][origin - 1] = weight;
        return true;
    }
}