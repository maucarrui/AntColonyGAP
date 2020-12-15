#ifndef SOLUTION_H
#define SOLUTION_H
#include "Solution.hpp"
#endif

class Ant {
    private:
        std::vector<std::pair<int, int>> travelledEdges;

    public:
        Ant();

        void addEdge(std::pair<int, int> edge);
        void sendToColony();
        Solution getSolution();
};
