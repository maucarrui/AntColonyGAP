#include <vector>

class HeuristicGraph {
    private:
        int numWorkers;
        int numTasks;

        std::vector<std::vector<double>> bipartite;
        std::vector<double> accumulatedPheromones;

        void setIntialPheromones();

    public:
        HeuristicGraph(int numWorkers, int numTasks);

        double getPheromone(int wID, int tID);
        double getAccumulated(int tID);

        void setPheromone(int wID, int tID, double pheromone);
        void updateAccumulated();
};
