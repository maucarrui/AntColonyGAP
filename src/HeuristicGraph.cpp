#include "HeuristicGraph.hpp"

/**
 * Constructor for the heuristic graph.
 * Graph where the ants will travel and 
 * deposit its pheromones.
 *
 * @param numWorkers The number of workers in the bipartite graph.
 * @param numTasks   The number of tasks in the bipartite graph.
 */
HeuristicGraph::HeuristicGraph(int numWorkers, int numTasks) {
    this->numWorkers = numWorkers;
    this->numTasks   = numTasks;

    this->bipartite.resize(numWorkers, std::vector<double>(numTasks));
    this->accumulatedPheromones.resize(numTasks);

    setInitialPheromones();
}

/**
 * Sets initial values of pheromones for the edges of the graph.
 * All the edges must have the same probability of beign explored
 * by ants in the beginning.
 */
void HeuristicGraph::setInitialPheromones() {
    int i, j;
    double pheromone;

    // For each edge adjecent to a Task.
    for (i = 0; i < numTasks; i++) {
	pheromone = 1;
	
	for (j = 0; j < numWorkers; j++)
	    bipartite[j][i] = pheromone;

	accumulatedPheromones[i] = numWorkers;
    }
}

/**
 + Returns the pheromone value of the edge (i, j) in the bipartite graph.
 * @param wID The worker's ID.
 * @param tID The task's ID.
 * @return The pheromone value of the edge (i, j) in the bipartite graph.
 */
double HeuristicGraph::getPheromone(int wID, int tID) const {
    return this->bipartite[wID][tID];
}

/**
 * Returns the accumulated amount of pheromones in a task.
 * @param  The task's ID.
 * @return The accumulated amount of pheromones in a task.
 */
double HeuristicGraph::getAccumulated(int tID) const {
    return this->accumulatedPheromones[tID];
}

/**
 * Set the pheromone value of the edge (i, j) in the bipartite.
 * @param i         The worker's ID.
 * @param j         The task's ID.
 * @param pheromone The new pheromone value.
 */
void HeuristicGraph::setPheromone(int i, int j, double pheromone) const {
    this->bipartite[i][j] = pheromone;
}

/**
 * Updates the amount of accumulated pheromones for each task.
 */
void HeuristicGraph::updateAccumulated() const {
    int i, j;
    double total;

    for (i = 0; i < numTasks; i++) {
        total = 0;

	for (j = 0; j < numWorkers; j++)
	    total += bipartite[j][i];
	
	accumulatedPheromones[i] = total;
    }
}
