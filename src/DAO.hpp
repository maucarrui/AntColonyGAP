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
	DAO(std::string location);

	int  openDB();
	void closeDB();
	
	Worker getWorkerByID(int ID);
	Task   getTaskByID(int ID);
	double getCapacity(int wID, int tID);
	double getCost(int wID, int tID);

        std::vector<Worker> getWorkers();
        std::vector<Task>   getTasks();
};
