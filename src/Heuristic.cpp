#include "Heuristic.hpp"

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
        this->ants.push_back(Ant());
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
    int i, j, k;
    int numWorkers = G.getNumWorkers();
    int numTasks   = G.getNumTasks();

    double r, edgeProb, accProb, accPheromone, pheromone;

    for (i = 0; i < numAnts; i++) {
        Ant ant = ants[i];
	
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
void updatePheromones() {
    int numEdges, i, j, wID, tID;
    double cost, capacity, newPheromone, workerCapacity;
    bool isFeasible;
    std::vector<std::pair<int, int>> edges;
    std::pair<int, int> edge;

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
    numEdges = ants[0].getSolution().getEdges().size();

    for (i = 0; i < numAnts; i++) {
        Solution s = ants[i].getSolution();
	edges = s.getEdges();
	cost  = G.calculateCost(edges);
	
	for (j = 0; j < numEdges; j++) {
	    isFeasible = true;
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

	    H.setPheromone(wID, tID, newPheromone);
	}

        // Update best solution if there is a better one.
	bestCost = bestSolution.getCost();
	if (isFeasible && (cost < bestCost)) {
	    bestSolution = s;
	    s.setCost(cost);
	}
    }

    H.updateAccumulated();
}

/**
 * Returns the ants to the colony.
 */
void returnAnts() {
    for (int i = 0; i < numAnts; i++)
        ants[i].sendToColony();
}
