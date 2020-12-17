#include <vector>

#ifndef SOLUTION_H
#define SOLUTION_H
#include "Solution.hpp"
#endif

class Ant {
    private:
        std::vector<std::pair<int, int>> travelledEdges;
        Solution solution;

        bool foundFood;

    public:
        Ant();

        void addEdge(std::pair<int, int> edge);
        void gotFood();
        void sendToColony();

        std::vector<std::pair<int, int>> getEdges();
        Solution getSolution();
        bool didFoundFood();
};
