#include <vector>
#include <string>
#include <math.h>

#ifndef GRAPH_H
#define GRAPH_H
#include "Graph.hpp"
#endif

class HeuristicGraph {
    private:
        int numWorkers;
        int numTasks;
        int alpha;
        int beta;

        const Graph &G;

        mutable std::vector<std::vector<double>> bipartite;
        mutable std::vector<double> accumulatedPheromones;
        mutable std::vector<double> accumulatedTotal;

        void setInitialPheromones();

    public:
        HeuristicGraph(int numWorkers, int numTasks, const Graph &G,
		       int alpha, int beta);

        double getPheromone(int wID, int tID) const;
        double getAccumulated(int tID) const;
        double getProbability(int wID, 
			      int tID, 
			      std::vector<std::pair<int, int>> edges) const;

        void setPheromone(int wID, int tID, double pheromone) const;
        void updateAccumulated() const;

        std::string showDistribution(int tID, 
				     std::vector<std::pair<int, int>> edges) const;
        std::string showPheromones(int tID) const;
        std::string showCosts(int tID) const;
        std::string showCapacities(int tID) const;
};
