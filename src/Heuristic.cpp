#include "Heuristic.hpp"
#include <iostream>

/**
 * Constructor for the Ant Colony Optimization (ACO)
 * heuristic.
 * 
 * @param G        The graph containing the cost and capacities.
 * @param H        The heuristic graph where the ants will travel.
 * @param Q        The heuristic parameter for updating pheromones.
 * @param numAnts  The number of ants in the heuristic.
 * @param epsilon  The desired at least value of the solution.
 * @param maxTries The max number of tries to find a solution.
 */
Heuristic::Heuristic(const Graph &G,
		     const HeuristicGraph &H,
		     double Q,
		     int numAnts,
		     double evaporation,
		     double epsilon,
		     int maxTries):
    G(G),
    H(H) {
    this->numAnts     = numAnts;
    this->evaporation = evaporation;
    this->epsilon     = epsilon;
    this->maxTries    = maxTries;

    for (int i = 0; i < numAnts; i++)
        ants.push_back(Ant());
}

/**
 * The ant colony optimization metaheuristic.
 */
void Heuristic::antColonyOptimization() {
    int i = 0;
    while (i < maxTries) {
        sendAnts();
	updatePheromones();
	returnAnts();
        i++;
    }
}

/**
 * Sends the ants to find a solution.
 */
void Heuristic::sendAnts() {
    int j, k;
    int numWorkers = G.getNumWorkers();
    int numTasks   = G.getNumTasks();

    double r, edgeProb, accProb, accPheromone, pheromone;

    std::list<Ant>::iterator it;

    for (it = ants.begin(); it != ants.end(); ++it) {
        Ant &ant = *it;
	
	// For each task the ant decides which
	// is the best worker to be assigned
	// depending on the pheromones left
	// by previous ants.
	for (j = 0; j < numTasks; j++) {
	    accProb      = 0;
	    r            = ((double) rand() / (RAND_MAX));
	    accPheromone = H.getAccumulated(j);

	    for (k = 0; k < numWorkers; k++) {
	        pheromone = H.getPheromone(k, j);
		edgeProb  = (pheromone / accPheromone);
		
		accProb += edgeProb;
		
		if (r <= accProb) {
		    ant.addEdge(std::make_pair(k + 1, j + 1));
		    break;
		}
	    }
	}
    }
}

/**
 * Updates the pheromones in the heuristic graph.
 */
void Heuristic::updatePheromones() {
    int numEdges, j, wID, tID;
    double cost, bestCost, capacity, newPheromone, workerCapacity;
    std::vector<std::pair<int, int>> edges;
    std::pair<int, int> edge;
    bool isFeasible = true;

    std::list<Ant>::iterator it;

    // First we evaporate all of the edges in the
    // heuristic graph.
    int numWorkers = G.getNumWorkers();
    int numTasks   = G.getNumTasks();

    for (wID = 0; wID < numWorkers; wID++) {
        for (tID = 0; tID < numTasks; tID++) {
	    newPheromone = (1 - evaporation) * H.getPheromone(wID, tID);
	    H.setPheromone(wID, tID, newPheromone);
	}
    }

    // Then we update the pheromones of edges where
    // ants travelled, checking if there is someone 
    // to penalize.
    numEdges = numWorkers;

    for (it = ants.begin(); it != ants.end(); it++) {
	edges      = it->getEdges();
	cost       = G.calculateCost(edges);
	isFeasible = true;
	
	for (j = 0; j < numEdges; j++) {
	    wID = edges[j].first;
	    tID = edges[j].second;
	    
	    // Update.
	    newPheromone = H.getPheromone(wID - 1, tID - 1) + (Q / cost);

	    // Check for feasability.
	    capacity       = G.getCapacityOf(wID, tID);
	    workerCapacity = G.getCapacityOfWorker(wID);

	    // If worker's capacity isn't enough for the task, 
	    // we penalize.
	    if (workerCapacity < capacity) {
	        isFeasible    = false;
	        newPheromone *= 0.2;
	    }

	    H.setPheromone(wID - 1, tID - 1, newPheromone);
	}


        // Update best solution if there is a better one.
	bestCost = bestSolution.getCost();
	if (bestSolution.getCost() == 0 || cost < bestCost) {
	    bestSolution = it->getSolution();
	    bestSolution.setCost(cost);
	    bestSolution.setFeasibility(isFeasible);
	}
    }

    H.updateAccumulated();
}

/**
 * Returns the ants to the colony.
 */
void Heuristic::returnAnts() {
    std::list<Ant>::iterator it;
    for (it = ants.begin(); it != ants.end(); it++)
        it->sendToColony();
}

/**
 * Returns a string representation of the best solution.
 * @return A string representation of the best solution.
 */
std::string Heuristic::printBestSolution() {
    return this->bestSolution.toString();
}
