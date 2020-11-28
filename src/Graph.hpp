#include <vector>

class Graph {
    private:
        int numWorkers;
	int numTasks;

	std::vector<std::vector<double>> capacityTable;
	std::vector<std::vector<double>> costTable;
    
    public:
	Graph(std::vector<Worker> workers,
	      std::vector<Task> tasks,
	      DAO dao);
	
	double getCapacityOf(int i, int j);
	double getCostOf(int i, int j);

}
