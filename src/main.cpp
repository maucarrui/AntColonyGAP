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
    s += "Usage: ./gap <datatabase.db> <randomSeed> \n";
    s += "Arguments: \n";
    s += "    <database.db>      The sqlite3 file containing all the information.\n";
    s += "    <randomSeed>       The seed for the RNG.\n";
    
    return s;
}

int main(int argc, char** argv) {

    if (argc != 3) {
        std::cout << usage() << std::endl;
	return -1;
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

    // Defining the heuristic.
    double Q           = 1;
    int numAnts        = 20;
    double evaporation = 0.010;
    int alpha          = 1;
    int beta           = 1;
    int maxTries       = 5000;
    
    // Build the heuristic graph.
    int numWorkers = workers.size();
    int numTasks   = tasks.size();
    HeuristicGraph H = HeuristicGraph(numWorkers, numTasks, G, alpha, beta);

    Heuristic heuristic = Heuristic(G,
				    H,
				    Q,
				    numAnts,
				    evaporation,
				    maxTries);
    
    heuristic.antColonyOptimization();

    std::string bestSolution = heuristic.printBestSolution();
    std::cout << bestSolution << std::endl;
}
