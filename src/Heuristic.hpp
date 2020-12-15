#include <vector>
#include <random>

#ifndef ANT_H
#define ANT_H
#include "Ant.hpp"
#endif

#ifndef GRAPH_H
#define GRAPH_H
#include "Graph.hpp"
#endif

#ifndef HEURISTIC_GRAPH_H
#define HEURISTIC_GRAPH_H
#include "HeuristicGraph.hpp"
#endif

#ifndef SOLUTION_H
#define SOLUTION_H
#include "Solution.hpp"
#endif

class Heuristic {
    private:
        const Graph &G;
        const HeuristicaGraph &H;

        int numAnts;
        double Q;
        double evaporation;
        double epsilon;

        std::vector<Ant> ants;

        Solution bestSolution;

    public:
        Heuristic(const Graph &G,
		  const HeuristicGraph &H,
		  double Q,
		  int numAnts,
		  double evaporation,
		  double epsilon,
		  int maxTries);

        void antColonyOptimization();
        void sendAnts();
        void updatePheromones();
        void returnAnts();
};
