#include "graph.h"
#include <vector>


Graph::Graph(const std::string &filename) {
    readGraphFromFile(filename);
}

void Graph::readGraphFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if(!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }
    int numEdges;
    file >> numVertices >> numEdges;

    adj.resize(numVertices);

    for(int i = 0; i < numEdges; i++) {
        int v, w;
        file >> v >> w;
        addEdge(v, w);
    }
    file.close();
}

int Graph::getNumVertices() const {
    return numVertices;
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
    adj[w].push_back(v);
}

void Graph::printGraph() {
    for (int i = 0; i < adj.size(); i++) {
        std::cout << "Vertex " << i << ": ";
        for(int neighbor : adj[i]) {
            std::cout << neighbor << " ";
        }
        std::cout << std::endl;
    }
}

const std::vector<int> &Graph::getAdj(int v) const {
    return adj[v];
}


