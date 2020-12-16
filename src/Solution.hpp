#include <vector>
#include <random>
#include <string>
#include <map>

class Solution {
    private:
        std::map<int, std::vector<int>> assignments;
        double capacity;
        double cost;
        bool isFeasible;

    public:
        Solution();

        void addAssignment(int wID, int tID);

        std::map<int, std::vector<int>> getAssignments();
        double  getCapacity();
        double  getCost();
        bool    getFeasibility();

        void setCapacity(double newCapacity);
        void setCost(double newCost);
        void setFeasibility(bool status);

        void clear();

        std::string toString();
};
