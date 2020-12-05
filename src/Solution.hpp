#include <vector>

class Solution {
    private:
        std::vector<std::pair<int, int>> edges;
        double capacity;
        double cost;
        bool isFeasible;

    public:
        Solution(std::vector<std::pair<int, int>> edges);

        double  getCapacity();
        double  getCost();
        bool    getFeasibilty();

        void setCapacity(double newCapacity);
        void setCost(double newCost);

        std::vector<std::pair<int, int>> getRandomNeighbor();
};
