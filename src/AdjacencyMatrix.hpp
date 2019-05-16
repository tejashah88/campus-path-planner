#ifndef ADJ_MAT_H
#define ADJ_MAT_H

// Yes, this is horribly inefficient in terms of space complexity, but it was
// relatively easy to implement at the time. Why? Because for each row/column
// pixel p, there's a maximum of 8 neighbors, while the adjacency matrix can
// store a maximum of n^2 neighbors, which n = rows * cols of pixels in an image.

class AdjacencyMatrix {
    private:
        int size;
        unsigned char **adj; // Using unsigned char since int takes 4 bytes and char takes only 1 byte

    public:
        AdjacencyMatrix(int size);
        ~AdjacencyMatrix();

        bool AddEdge(int origin, int dest, int weight);
        bool AddEdge(int origin, int dest) { return this->AddEdge(origin, dest, 1); };

        unsigned char** GetAdjMatrixPointer() const { return this->adj; }
        int GetSize() const { return this->size; }
};

#endif // ADJ_MAT_H