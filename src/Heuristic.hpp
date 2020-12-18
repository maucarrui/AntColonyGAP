#include <list>
#include <random>
#include <string>
#include <math.h>

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
        const HeuristicGraph &H;

        int numAnts;
        int maxTries;
        double Q;
        double evaporation;

        double disipation;
        double decayment;
        double epsilon;

        std::list<Ant> ants;

        Solution bestSolution;

        void sendAnts();
        void updatePheromones();
        void returnAnts();

    public:
        Heuristic(const Graph &G,
		  const HeuristicGraph &H,
		  double Q,
		  int numAnts,
		  double evaporation,
		  int maxTries);

        void antColonyOptimization();

        std::string printBestSolution();
};
