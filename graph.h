#ifndef VERTEXCOVER_GRAPH_H
#define VERTEXCOVER_GRAPH_H

#include <vector>
#include <fstream>
#include <iostream>

class Graph {
public:
    Graph(const std::string& filename);
    int getNumVertices() const;
    void addEdge(int v, int w);
    void printGraph();
    const std::vector<int>& getAdj(int v) const;

private:
    int numVertices;
    std::vector<std::vector<int>> adj;
    void readGraphFromFile(const std::string& filename);
};


#endif //VERTEXCOVER_GRAPH_H
