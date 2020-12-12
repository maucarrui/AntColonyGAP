#include "HeuristicGraph.hpp"

/**
 * Constructor for the heuristic graph.
 * Graph where the ants will travel and 
 * deposit its pheromones.
 *
 * @param numWorkers The number of workers in the bipartite graph.
 * @param numTasks   The number of tasks in the bipartite graph.
 */
HueristicGraph::HeuristicGraph(int numWorkers, int numTasks) {
    this->numWorkers = numWorkers;
    this->numTasks   = numTasks;

    this->bipartite.resize(numWorkers, 
			   std::vector<std::pair<double, double>>(numTasks));
    this->clan.resize(numWorkers, std::vector<double>(numWorkers));

    setInitialPheromones();
}

/**
 * Sets initial values of pheromones for the edges of the graph.
 * All the edges must have the same probability of beign explored
 * by ants in the beginning.
 */
void HeuristicGraph::setInitialPheromones() {
    int i, j, totalEdges;
    double probabilty;

    // For each edge adjecent to a worker.
    for (i = 0; i < numWorkers; i++) {
        totalEdges  = (numWorkers - 1) + numTasks;
	probability = 1 / totalEdges;

	// Clan
	for (j = i + 1; j < numWorkers; j++) {
	    clan[i][j] = probability;
	    clan[j][i] = probability;
	}
	
	// Bipartite
	for (j = 0; j < numTasks; j++)
	    bipartite[i][j].first = probability;
    }

    // For each edge adjecent to a Task.
    for (i = 0; i < numTasks; i++) {
        totalEdges = numWorkers;
	probability = 1 / totalEdges;
	
	for (j = 0; j < numWorkers; j++)
	    bipartite[j][i].second = probability;
    }
}

/**
 * Returns the pheromone value of the edge (i, j) in the clan.
 * @param i The worker's ID.
 * @param j The worker's ID.
 * @return The pheromone value of the edge (i, j) in the clan.
 */
double HueristicGraph::getPheromoneClan(int i, int j) {
    return this->clan[i][j];
}

/**
 + Returns the pheromone value of the edge (i, j) in the bipartite graph.
 * @param wID The worker's ID.
 * @param tID The task's ID.
 * @return The pheromone value of the edge (i, j) in the bipartite graph.
 */
double HeuristicGraph::getPheromoneBipartite(int wID, int tID) {
    return this->bipartite[i][j];
}

/**
 * Set the pheromone value of the edge (i, j) in the clan.
 * @param i         The worker's ID.
 * @param j         The worker's ID.
 * @param pheromone The new pheromone value.
 */
void HeuristicGraph::setPheromoneClan(int i, int j, double pheromone) {
    this->clan[i][j] = pheromone;
}

/**
 * Set the pheromone value of the edge (i, j) in the bipartite.
 * @param i         The worker's ID.
 * @param j         The task's ID.
 * @param pheromone The new pheromone value.
 */
void HeuristicGraph::setPheromoneBipartite(int i, int j, double pheromone) {
    this->bipartite[i][j] = pheromone;
}
