#include "Graph.hpp"

/**
 * Constructor for a graph.
 * The complete bipartite graph has an independent
 * set of vertex representing the workers and 
 * another independent set of vertex representing
 * the tasks. The edges connecting this two 
 * sets represent the worker's capacity of doing 
 * a task and its cost.
 *
 * @param workers The set of workers.
 * @param tasks   The set of tasks.
 * @param DAO     The database access object.
 */
Graph::Graph(const std::vector<Worker> &workers,
	     const std::vector<Task>   &tasks,
	     const DAO &dao) {
    this->workers = workers;
    this->tasks   = tasks;
    this->dao     = dao;

    this->numWorkers = workers.size();
    this->numTasks   = tasks.size();

    this->capacityTable.resize(numWorkers, std::vector<double>(numTasks));
    this->costTable.resize(numWorkers, std::vector<double>(numTasks));
}

/**
 * Returns the amount of workers the graph has.
 * @return The amount of workers the graph has.
 */
int Graph::getNumWorkers() {
    return this->workers.size();
}

/**
 * Returns the amount of tasks the graph has.
 * @return The amount of tasks the graph has.
 */
int Graph::getNumTasks() {
    return this->tasks.size();
}

/**
 * Returns the amount of edges the graph has.
 * @return The amount of edges the graph has.
 */
int Graph::getNumEdges() {
    return capacityTable.size() * capacityTable[0].size();
}

/**
 * Returns the worker's capacity of doing a task.
 * @param i The worker's index.
 * @param j The task's index.
 * @return The worker's capacity of doing a task.
 */
double Graph::getCapacityOf(int i, int j) {
    return 0;
}

/**
 * Returns the cost of the completion of a task by a worker.
 * @param i The worker's index.
 * @param j The task's index.
 * @return The cost of the completion of a task by a worker.
 */
double Graph::getCostOf(int i, int j) {
    return 0;
}
