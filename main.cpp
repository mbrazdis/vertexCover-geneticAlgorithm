#include <iostream>
#include "graph.h"
#include "vertex_cover_ga.h"

int main() {
    std::string filename = "/Users/mikebraz/Desktop/faculta/ACC/vertexCover/graph.txt";
    Graph graph(filename);

    graph.printGraph();

    Vertex_cover_ga ga(graph, 50, 100, 0.7, 0.01);
    std::vector<int> vertexCover = ga.findMinimumVertexCover();

    std::cout << "Minimum Vertex Cover: ";
    for(int v : vertexCover) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
    return 0;
}
