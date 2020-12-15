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
double Graph::getCapacityOf(int i, int j) {
    return capacityTable[i-1][j-1];
}

/**
 * Returns the cost of the completion of a task by a worker.
 * @param i The worker's ID.
 * @param j The task's ID.
 * @return The cost of the completion of a task by a worker.
 */
double Graph::getCostOf(int i, int j) {
    return costTable[i-1][j-1];
}

/**
 * Returns the worker's capacity.
 * @param wID The worker's ID.
 * @return The worker's capacity.
 */
double Graph::getCapacityOfWorker(int wID) {
    return searchTableWorkers[wID].getCapacity();
}
/**
 * Calculates the capacity of a set of edges.
 * @return The capacity of the set of edges.
 */
double Graph::calculateCapacity(std::vector<std::pair<int, int>> edges) {
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
double Graph::calculateCost(std::vector<std::pair<int, int>> edges) {
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
 * Returns an initial solution given the current set 
 * of workers and tasks.
 * @return An initial solution.
 */
Solution Graph::getInitialSolution() {
    std::vector<std::pair<int, int>> edges;
    int i, r, wID, tID;

    for (i = 0; i < numTasks; i++) {
        // Select a task.
        Task t = tasks[i];
	
	// Select a random worker;
	r = rand() % numWorkers;
	Worker w = workers[r];
	
	// Assign the worker to the task.
	wID = w.getID();
	tID = t.getID();

	edges.push_back(std::make_pair(wID, tID));
    }

    // Create a solution
    Solution s = Solution(edges);

    // Calculate its capacity and cost.
    double capacity = calculateCapacity(edges);
    double cost     = calculateCost(edges);

    s.setCapacity(capacity);
    s.setCost(cost);

    return s;
}
