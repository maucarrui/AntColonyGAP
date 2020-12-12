#include <vector>

class HeuristicGraph {
    private:
        int numWorkers;
        int numTasks;

        std::vector<std::vector<std::pair<double, double>>> bipartite;
        std::vector<std::vector<double>> clan;

        void setIntialPheromones();

    public:
        HeuristicGraph(int numWorkers, int numTasks);

        double getPheromoneClan(int i, int j);
        double getPheromoneBipartite(int wID, int tID);

        void setPheromoneClan(int i, int j, double pheromone);
        void setPheromoneBipartite(int wID, int tID, double pheromone);
}
