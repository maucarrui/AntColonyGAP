#include <vector>

#ifndef SOLUTION_H
#define SOLUTION_H
#include "Solution.hpp"
#endif

class Ant {
    private:
        std::vector<std::pair<int, int>> travelledEdges;
        Solution solution;

    public:
        Ant();

        void addEdge(std::pair<int, int> edge);
        std::vector<std::pair<int, int>> getEdges();
        void sendToColony();
        Solution getSolution();
};
