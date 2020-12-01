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
Graph::Graph(std::vector<Worker> workers,
	     std::vector<Task> tasks,
	     DAO dao) {
    return;
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
