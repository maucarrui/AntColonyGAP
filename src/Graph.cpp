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
	     const DAO &dao):
    workers(workers),
    tasks(tasks),
    dao(dao) {
    this->numWorkers = workers.size();
    this->numTasks   = tasks.size();

    this->capacityTable.resize(numWorkers, std::vector<double>(numTasks));
    this->costTable.resize(numWorkers, std::vector<double>(numTasks));

    buildCapacityTable();
    buildCostTable();
    buildSearchTable();
}

/**
 * Returns the amount of workers the graph has.
 * @return The amount of workers the graph has.
 */
int Graph::getNumWorkers() const {
    return this->workers.size();
}

/**
 * Returns the amount of tasks the graph has.
 * @return The amount of tasks the graph has.
 */
int Graph::getNumTasks() const {
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
 * Builds the search table of workers.
 */
void Graph::buildSearchTable() {
    for (int i = 0; i < numWorkers; i++) {
        Worker w = workers[i];
	searchTableWorkers[w.getID()] = w;
    }
}

/**
 * Builds the capacity table.
 */
void Graph::buildCapacityTable() {
    std::vector<std::pair<std::pair<int, int>, double>> capacities;
    capacities = dao.getCapacities();
    
    int tID, wID, k;
    int totalEdges = numWorkers * numTasks;

    for (k = 0; k < totalEdges; k++) {
        tID = capacities[k].first.first - 1;
	wID = capacities[k].first.second - 1;
	capacityTable[wID][tID] = capacities[k].second;
    }
}

/**
 * Builds the cost table.
 */
void Graph::buildCostTable() {
    std::vector<std::pair<std::pair<int, int>, double>> costs;
    costs = dao.getCosts();
    
    int tID, wID, k;
    int totalEdges = numWorkers * numTasks;

    for (k = 0; k < totalEdges; k++) {
        tID = costs[k].first.first - 1;
	wID = costs[k].first.second - 1;
	costTable[wID][tID] = costs[k].second;
    }
}

/**
 * Returns the worker's capacity of doing a task.
 * @param i The worker's ID.
 * @param j The task's ID.
 * @return The worker's capacity of doing a task.
 */
double Graph::getCapacityOf(int i, int j) const {
    return capacityTable[i-1][j-1];
}

/**
 * Returns the cost of the completion of a task by a worker.
 * @param i The worker's ID.
 * @param j The task's ID.
 * @return The cost of the completion of a task by a worker.
 */
double Graph::getCostOf(int i, int j) const {
    return costTable[i-1][j-1];
}

/**
 * Returns the worker's capacity.
 * @param wID The worker's ID.
 * @return The worker's capacity.
 */
double Graph::getCapacityOfWorker(int wID) const {
    std::unordered_map<int, Worker>::const_iterator it;
    it = searchTableWorkers.find(wID);

    return it->second.getCapacity();
}
/**
 * Calculates the capacity of a set of edges.
 * @return The capacity of the set of edges.
 */
double Graph::calculateCapacity(std::vector<std::pair<int, int>> edges) const {
    int numEdges = edges.size();
    int i, wID, tID;
    double total = 0;

    for (i = 0; i < numEdges; i++) {
        wID = edges[i].first;
	tID = edges[i].second;
	
	total += getCapacityOf(wID, tID);
    }

    return total;
}

/**
 * Calculates the cost of a set of edges.
 * @return The cost of the set of edges.
 */
double Graph::calculateCost(std::vector<std::pair<int, int>> edges) const {
    int numEdges = edges.size();
    int i, wID, tID;
    double total = 0;

    for (i = 0; i < numEdges; i++) {
        wID = edges[i].first;
	tID = edges[i].second;
	
	total += getCostOf(wID, tID);
    }

    return total;
}


/**
 * Returns whether or not a worker is capable of doing a task.
 * @param wID The worker's ID.
 * @param tID The task's ID.
 * @return True if the worker is capable, false otherwise.
 */
bool Graph::checkIfCapable(int wID, int tID) const {
    double capacity  = getCapacityOf(wID, tID);
    double wCapacity = getCapacityOfWorker(wID);
    
    return (capacity <= wCapacity);
}

/**
 * Checks whether or not a set of edges its feasable or not.
 * @param  edges The set of edges.
 * @return True if it is feasible, false otherwise.
 */
bool Graph::checkFeasibility(std::vector<std::pair<int, int>> edges) const {
    std::unordered_map<int, double> assignments;
    std::unordered_map<int, double>::iterator it;

    double capacity;

    int i, wID, tID;
    int numEdges = edges.size();

    // Add tasks by worker.
    for (i = 0; i < numEdges; i++) {
        wID = edges[i].first;
	tID = edges[i].second;

	it = assignments.find(wID);
	    
	if (it == assignments.end())
	    assignments[wID]  = getCapacityOf(wID, tID);
	else
	    assignments[wID] += getCapacityOf(wID, tID);

	capacity = getCapacityOfWorker(wID);
	
	if (capacity < assignments[wID])
	    return false;
    }

    return true;
}
