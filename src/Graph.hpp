#include <vector>

#ifndef WORKER_H
#define WORKER_H
#include "Worker.hpp"
#endif

#ifndef TASK_H
#define TASK_H
#include "Task.hpp"
#endif

#ifndef DAO_H
#define DAO_H
#include "DAO.hpp"
#endif

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

};
