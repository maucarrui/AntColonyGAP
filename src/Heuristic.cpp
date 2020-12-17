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
		     int maxTries):
    G(G),
    H(H) {
    this->numAnts     = numAnts;
    this->evaporation = evaporation;
    this->maxTries    = maxTries;
    this->Q           = Q;

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

    double r, edgeProb, accProb;
    
    bool foundFood;

    std::list<Ant>::iterator it;
    std::vector<std::pair<int, int>> currentSolution;

    int a = 0;
    for (it = ants.begin(); it != ants.end(); ++it) {
        Ant &ant  = *it;
	
	// For each task the ant decides which
	// is the best worker to be assigned
	// depending on the pheromones left
	// by previous ants.
	for (j = 0; j < numTasks; j++) {
	    accProb      = 0;
	    r            = ((double) rand() / (RAND_MAX));
	    foundFood    = false;

	    for (k = 0; k < numWorkers; k++) {
                currentSolution = ant.getEdges();

		currentSolution.push_back(std::make_pair(k + 1, j + 1));

		edgeProb = H.getProbability(k, j);

		// If the solution is not feasible anymore.
		if (!G.checkFeasibility(currentSolution))
		    edgeProb *= 0;
		
		if (edgeProb != 0)
                    foundFood = true;
		
		accProb += edgeProb;
		
		if (r <= accProb) {
		    ant.addEdge(std::make_pair(k + 1, j + 1));
		    break;
		}
	    }

	    if (!foundFood)
	        break;
	}

	if (foundFood)
	    ant.gotFood();

	a++;
    }
}

/**
 * Updates the pheromones in the heuristic graph.
 */
void Heuristic::updatePheromones() {
    int numEdges, j, wID, tID;
    double cost, capacity, bestCost, newPheromone;
    std::vector<std::pair<int, int>> edges;
    std::pair<int, int> edge;
    bool isFeasible = true;

    std::vector<std::pair<std::pair<int, int>, double>> p;
    double penalization;

    std::list<Ant>::iterator ant;

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

    for (ant = ants.begin(); ant != ants.end(); ant++) {
        if (ant->didFoundFood()) {
	    edges      = ant->getEdges();
	    cost       = G.calculateCost(edges);
	    isFeasible = true;

	    for (j = 0; j < numEdges; j++) {
	        wID = edges[j].first;
	        tID = edges[j].second;
	    
		// Update.
		newPheromone = H.getPheromone(wID - 1, tID - 1) + (Q / cost);

		H.setPheromone(wID - 1, tID - 1, newPheromone);
	    }

	    /*
	    // Penalization time.
	    p = G.checkFeasibility(edges);
	    
	    if (!p.empty()) {
	        isFeasible = false;
		numEdges   = p.size();
	    
		for (j = 0; j < numEdges; j++) {
	            wID          = p[j].first.first;
		    tID          = p[j].first.second;
		    penalization = p[j].second;

		    newPheromone  = H.getPheromone(wID - 1, tID - 1);
		    newPheromone *= (1 - penalization);

		    H.setPheromone(wID - 1, tID - 1, newPheromone);
		}
	    }
	    */

	    // Update best solution if there is a better one.
	    bestCost = bestSolution.getCost();
	    if (bestSolution.getCost() == 0 || cost < bestCost) {
                capacity     = G.calculateCapacity(edges);
		bestSolution = ant->getSolution();
		bestSolution.setCost(cost);
		bestSolution.setCapacity(capacity);
		bestSolution.setFeasibility(isFeasible);
	    }
	}
    }

    H.updateAccumulated();

    // std::cout << H.showPheromones(0) << std::endl;
    // std::cout << H.showDistribution(0) << std::endl;
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
