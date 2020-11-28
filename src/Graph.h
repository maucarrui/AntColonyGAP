#include <vector>

class Graph {
    private:
        int numWorkers;
	int numTasks;

	std::vector<std::vector<double>> capacityTable;
	std::vector<std::vector<double>> taskTable;
    
    public:
	Graph(std::vector<Worker> workers,
	      std::vector<Task> tasks,
	      DAO dao);
	
	double getCapacityOf(int i, int j);
	double getTaskOf(int i, int j);

}
