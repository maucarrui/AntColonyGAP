#include <sqlite3.h>
#include <string>
#include <vector>
#include <iostream>

#ifndef WORKER_H
#define WORKER_H
#include "Worker.hpp"
#endif

#ifndef TASK_H
#define TASK_H
#include "Task.hpp"
#endif

class DAO {
    private:
        sqlite3* DB;
	std::string location;

    public:
        DAO();
	DAO(std::string location);

	int  openDB();
	void closeDB();
	
	Worker getWorkerByID(int ID) const;
	Task   getTaskByID(int ID) const;
	double getCapacity(int wID, int tID) const;
	double getCost(int wID, int tID) const;

        std::vector<Worker> getWorkers() const;
        std::vector<Task>   getTasks() const;

        std::vector<std::pair<std::pair<int, int>, double>> getCapacities() const;
        std::vector<std::pair<std::pair<int, int>, double>> getCosts() const;
};
