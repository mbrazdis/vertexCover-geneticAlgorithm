#include "vertex_cover_ga.h"
#include <algorithm>
#include <random>
#include <ctime>
#include <cstdlib>
#include <iostream>

Vertex_cover_ga::Vertex_cover_ga(const Graph &graph, int populationSize, int generations, double crossoverRate, double mutationRate)
        : graph(graph), populationSize(populationSize), generations(generations), crossoverRate(crossoverRate), mutationRate(mutationRate) {
    std::srand(static_cast<unsigned>(std::time(0)));
    initializePopulation();
}

void Vertex_cover_ga::initializePopulation() {
    std::default_random_engine generator(static_cast<unsigned>(std::time(0)));
    std::uniform_int_distribution<int> distribution(0, 1);

    for (int i = 0; i < populationSize; i++) {
        Individual individual;
        individual.chromosome = std::vector<int>(graph.getNumVertices());
        for (int j = 0; j < graph.getNumVertices(); j++) {
            individual.chromosome[j] = distribution(generator);
        }
        population.push_back(individual);
    }
    evaluateFitness();
    std::cout << "Initial Population:\n";
    for (const auto& individual : population) {
        std::cout << "Chromosome: ";
        for (int gene : individual.chromosome) {
            std::cout << gene << " ";
        }
        std::cout << "Fitness Value: " << individual.fitness << std::endl;
    }
    std::cout << std::endl;
}

void Vertex_cover_ga::evaluateFitness() {
    for (auto& individual : population) {
        int coverSize = std::count(individual.chromosome.begin(), individual.chromosome.end(), 1);
        int coverEdges = 0;
        int totalEdges = 0;

        for (int v = 0; v < graph.getNumVertices(); v++) {
            for (int w : graph.getAdj(v)) {
                if (v < w) {
                    totalEdges++;
                    if (individual.chromosome[v] == 1 || individual.chromosome[w] == 1) {
                        coverEdges++;
                    }
                }
            }
        }
        individual.fitness = coverSize + (totalEdges - coverEdges);
    }
}


Vertex_cover_ga::Individual Vertex_cover_ga::crossover(const Vertex_cover_ga::Individual &parent1, const Vertex_cover_ga::Individual &parent2) {
    Individual offspring;
    offspring.chromosome.resize(graph.getNumVertices());
    std::default_random_engine generator(std::rand());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    for(int i = 0; i < graph.getNumVertices(); i++) {
        offspring.chromosome[i] = distribution(generator) < crossoverRate ? parent1.chromosome[i] : parent2.chromosome[i];
    }

    return offspring;
}

void Vertex_cover_ga::mutate(Vertex_cover_ga::Individual &individual) {
    std::default_random_engine generator(std::rand());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    for(int i = 0; i < graph.getNumVertices(); i++) {
        if (distribution(generator) < mutationRate) {
            individual.chromosome[i] = 1 - individual.chromosome[i];
        }
    }
}

Vertex_cover_ga::Individual Vertex_cover_ga::selectParent() {
    double totalFitness = 0.0;
    for(const auto& individual : population) {
        totalFitness += 1.0 / (1 + individual.fitness);
    }

    double randomFitness = (rand() / static_cast<double>(RAND_MAX)) * totalFitness;
    double currentFitness = 0.0;

    for (const auto& individual : population) {
        currentFitness += 1.0 / (1 + individual.fitness);
        if(currentFitness >= randomFitness) {
            return individual;
        }
    }
    return population.back();
}

std::vector<int> Vertex_cover_ga::decodeSolution(const Vertex_cover_ga::Individual &individual) {
    std::vector<int> solution;
    for (int i = 0; i < graph.getNumVertices(); i++) {
        if (individual.chromosome[i] == 1) {
            solution.push_back(i);
        }
    }
    return solution;
}

std::vector<int> Vertex_cover_ga::findMinimumVertexCover() {
    for (int gen = 0; gen < generations; gen++) {
        std::vector<Individual> newPopulation;
        for(int i = 0; i < populationSize; i++) {
            Individual parent1 = selectParent();
            Individual parent2 = selectParent();
            Individual offspring = crossover(parent1, parent2);
            mutate(offspring);
            newPopulation.push_back(offspring);
        }
        population = newPopulation;
        evaluateFitness();

        std::cout << "Generation " << gen + 1 << ":\n";
        for (const auto& individual : population) {
            std::cout << "Chromosome: ";
            for(int gene : individual.chromosome) {
                std::cout << gene << " ";
            }
            std::cout << "Fitness Value: " << individual.fitness << std::endl;
        }
        std::cout << std::endl;
    }

    Individual bestIndividual = *std::min_element(population.begin(), population.end(), [](const Individual& a, const Individual& b) {
        return a.fitness < b.fitness;
    });

    std::cout << "Best Chromosome: ";
    for (int gene : bestIndividual.chromosome) {
        std::cout << gene << " ";
    }
    std::cout << std::endl << "Fitness Value: " << bestIndividual.fitness << std::endl;

    return decodeSolution(bestIndividual);
}
