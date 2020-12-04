#include <iostream>
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

        const std::vector<Worker>& workers;
        const std::vector<Task>&   tasks;

        const DAO& dao;

	std::vector<std::vector<double>> capacityTable;
	std::vector<std::vector<double>> costTable;

        void buildCapacityTable();
        void buildCostTable();
    
    public:
	Graph(const std::vector<Worker> &workers,
	      const std::vector<Task>   &tasks,
	      const DAO &dao);

        int getNumWorkers();
        int getNumTasks();
        int getNumEdges();
	
	double getCapacityOf(int i, int j);
	double getCostOf(int i, int j);

};
