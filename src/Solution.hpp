#include <vector>
#include <random>

class Solution {
    private:
        std::vector<std::pair<int, int>> edges;
        double capacity;
        double cost;
        bool isFeasible;

    public:
        Solution();
        Solution(std::vector<std::pair<int, int>> edges);

        std::vector<std::pair<int, int>> getEdges();
        double  getCapacity();
        double  getCost();
        bool    getFeasibility();

        void setCapacity(double newCapacity);
        void setCost(double newCost);
};
