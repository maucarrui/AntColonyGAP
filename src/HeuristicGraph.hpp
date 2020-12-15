#include <vector>

class HeuristicGraph {
    private:
        int numWorkers;
        int numTasks;

        mutable std::vector<std::vector<double>> bipartite;
        mutable std::vector<double> accumulatedPheromones;

        void setInitialPheromones();

    public:
        HeuristicGraph(int numWorkers, int numTasks);

        double getPheromone(int wID, int tID) const;
        double getAccumulated(int tID) const;

        void setPheromone(int wID, int tID, double pheromone) const;
        void updateAccumulated() const;
};
