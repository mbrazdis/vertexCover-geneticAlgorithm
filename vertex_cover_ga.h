#ifndef VERTEX_COVER_GA_H
#define VERTEX_COVER_GA_H

#include "graph.h"
#include <vector>

class Vertex_cover_ga {
public:
    Vertex_cover_ga(const Graph& graph, int populationSize, int generations, double crossoverRate, double mutationRate);
    std::vector<int> findMinimumVertexCover();

private:
    struct Individual {
        std::vector<int> chromosome;
        int fitness;
    };

    void initializePopulation();
    void evaluateFitness();
    Individual crossover(const Individual& parent1, const Individual& parent2);
    void mutate(Individual& individual);
    Individual selectParent();
    std::vector<int> decodeSolution(const Individual& individual);

    const Graph& graph;
    int populationSize;
    int generations;
    double crossoverRate;
    double mutationRate;
    std::vector<Individual> population;
};

#endif//VERTEXCOVER_VERTEX_COVER_GA_H
