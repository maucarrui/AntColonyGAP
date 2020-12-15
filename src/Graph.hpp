#include <iostream>
#include <vector>
#include <random>
#include <unordered_map>

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

#ifndef SOLUTION_H
#define SOLUTION_H
#include "Solution.hpp"
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

        std::unordered_map<int, Worker> searchTableWorkers;

        void buildSearchTable();
        void buildCapacityTable();
        void buildCostTable();
    
    public:
	Graph(const std::vector<Worker> &workers,
	      const std::vector<Task>   &tasks,
	      const DAO &dao);

        int getNumWorkers() const;
        int getNumTasks() const;
        int getNumEdges();
	
	double getCapacityOf(int i, int j);
	double getCostOf(int i, int j);

        double getCapacityOfWorker(int wID);

        double calculateCapacity(std::vector<std::pair<int, int>> edges);
        double calculateCost(std::vector<std::pair<int, int>> edges);

        Solution getInitialSolution();
};
