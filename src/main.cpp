#include <iostream>
#include <string>
#include <list>

#ifndef ANT_H
#define ANT_H
#include "Ant.hpp"
#endif

#ifndef DAO_H
#define DAO_H
#include "DAO.hpp"
#endif

#ifndef GRAPH_H
#define GRAPH_H
#include "Graph.hpp"
#endif

#ifndef HEURISTIC_GRAPH_H
#define HEURISTIC_GRAPH_H
#include "HeuristicGraph.hpp"
#endif

#ifndef HEURISTIC
#define HEURISTIC
#include "Heuristic.hpp"
#endif

#ifndef TASK_H
#define TASK_H
#include "Task.hpp"
#endif

#ifndef WORKER_H
#define WORKER_H
#include "Worker.hpp"
#endif

/**
 * Returns the usage of this program.
 * @return the usage of this program.
 */
std::string usage() {
    std::string s = "";
    s += "Usage: ./gap <datatabase.db> <randomSeed> [option] \n";
    s += "Arguments: \n";
    s += "    <database.db>      The sqlite3 file containing all the information.\n";
    s += "    <randomSeed>       The seed for the RNG.\n";
    s += "Options: \n";
    s += "    --verbose          Prints a more detailed execution of the TSP.\n";
    s += "    --onlycost         Prints only the cost of the best found solution.\n";
    
    return s;
}

int main(int argc, char** argv) {
    bool activeOption = false;
    bool costOption   = false;

    if (argc < 3 || argc > 4) {
        std::cout << usage() << std::endl;
	return -1;
    } else if (argc == 4) {
        std::string option1 = "--verbose";
	std::string option2 = "--onlycost";
	
	if (!option1.compare(argv[4]))
	    activeOption = true;

	else if (!option2.compare(argv[4]))
	    costOption = true;

	else {
	    std::cout << usage() << std::endl;
	    return -1;
	}
    }

    // Get the path of the sql file and the RNG seed.
    std::string pathDB = argv[1];
    int seed           = std::stoi(argv[2]);

    // Set the seed for the RNG.
    std::srand(seed);

    // Get the DAO.
    DAO dao = DAO(pathDB);
    dao.openDB();

    // Get all of the workers and tasks.
    std::vector<Worker> workers = dao.getWorkers();
    std::vector<Task>   tasks   = dao.getTasks();
    
    // Build the graph.
    Graph G = Graph(workers, tasks, dao);

    // Close DB connection.
    dao.closeDB();
    
    // Build the heuristic graph.
    int numWorkers = workers.size();
    int numTasks   = tasks.size();
    HeuristicGraph H = HeuristicGraph(numWorkers, numTasks);

    // Defining the heuristic.
    double Q           = 1;
    int numAnts        = 20;
    double evaporation = 0.2;
    double epsilon     = 0.0010;
    int maxTries       = 50;

    Heuristic heuristic = Heuristic(G,
				    H,
				    Q,
				    numAnts,
				    evaporation,
				    epsilon,
				    maxTries);
    
    heuristic.antColonyOptimization();

    std::string bestSolution = heuristic.printBestSolution();
    std::cout << bestSolution << std::endl;
}
