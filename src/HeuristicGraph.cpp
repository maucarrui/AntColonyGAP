#include "HeuristicGraph.hpp"

/**
 * Constructor for the heuristic graph.
 * Graph where the ants will travel and 
 * deposit its pheromones.
 *
 * @param numWorkers The number of workers in the bipartite graph.
 * @param numTasks   The number of tasks in the bipartite graph.
 */
HeuristicGraph::HeuristicGraph(int numWorkers, int numTasks, 
			       const Graph &G, int alpha, int beta):
    G(G) {
    this->numWorkers = numWorkers;
    this->numTasks   = numTasks;
    this->alpha      = alpha;
    this->beta       = beta;

    this->bipartite.resize(numWorkers, std::vector<double>(numTasks));
    this->accumulatedPheromones.resize(numTasks);
    this->accumulatedTotal.resize(numTasks);

    setInitialPheromones();
}

/**
 * Sets initial values of pheromones for the edges of the graph.
 * All the edges must have the same probability of beign explored
 * by ants in the beginning.
 */
void HeuristicGraph::setInitialPheromones() {
    int i, j;
    double pheromone, heuristic;

    // For each edge adjecent to a Task.
    for (i = 0; i < numTasks; i++) {
	pheromone = 1;
	
	for (j = 0; j < numWorkers; j++) {
	    heuristic = 1 / G.getCapacityOf(j+1, i+1);

	    bipartite[j][i]      = pheromone;
	    accumulatedTotal[i] += pow(heuristic, beta); 
	}

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
 * Returns the probability of using this edge.
 * @return The probability of using this edge.
 */
double HeuristicGraph::getProbability(int wID, 
				      int tID, 
				      std::vector<std::pair<int, int>> edges) const {
    double pheromone, heuristic, acc;
    std::vector<std::pair<int, int>> current;

    current = edges;
    current.push_back(std::make_pair(wID + 1, tID + 1));

    // If the solution is not feasible anymore.
    if (!G.checkFeasibility(current))
        return 0;

    pheromone = pow(bipartite[wID][tID], alpha);
    heuristic = pow((1 / G.getCapacityOf(wID + 1, tID + 1)), beta);
    
    acc = accumulatedTotal[tID];

    return (pheromone * heuristic) / acc;
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
    double totalPheromones;
    double total, heuristic, pheromone;

    for (i = 0; i < numTasks; i++) {
        totalPheromones = 0;
	total = 0;

	for (j = 0; j < numWorkers; j++) {
	    heuristic = (1 / G.getCapacityOf(j+1, i+1));
	    pheromone = bipartite[j][i];

	    totalPheromones += bipartite[j][i];
	    total           += pow(pheromone, alpha) * pow(heuristic, beta);
	}
	
	accumulatedPheromones[i] = totalPheromones;
	accumulatedTotal[i]      = total;
    }
}

/**
 * Returns a string representation of the distribution
 * of a task. The distribution of a task consists in the 
 * probabilities to choose a worker's edge.
 * @param tID The task's ID.
 * @return A string representation of the distribution.
 */
std::string 
HeuristicGraph::showDistribution(int tID,
				 std::vector<std::pair<int, int>> edges) const {
    std::string s;
    int i;
    double prob;
    
    int numEdges = edges.size();

    s  = "Distribución de la tarea " + std::to_string(tID + 1) + "\n";

    s += "Dada la secuencia: {";
    if (!edges.empty()) {
        for (i = 0; i < numEdges; i++) {
            if (i == numEdges - 1) {
	        s += " (" + std::to_string(edges[i].first) + ", ";
		s += std::to_string(edges[i].second) + ") }\n";
	    }
	    else {
	        s += "(" + std::to_string(edges[i].first) + ", ";
	        s += std::to_string(edges[i].second) + ") ,";
	    }
	}
    } else {
        s += "}\n";
    }

    for (i = 0; i < numWorkers; i++) {
	prob      = getProbability(i, tID, edges);
        
        s += "  W" + std::to_string(i + 1) + ": ";
	s += std::to_string(prob) + "\n";
    }

    return s;
}

/**
 * Returns a string representation of the pheromones of a task. 
 * @param tID The task's ID.
 * @return A string representation of the distribution.
 */
std::string HeuristicGraph::showPheromones(int tID) const {
    std::string s;
    int i;
    double pheromone;

    s = "Feromonas de la tarea " + std::to_string(tID + 1) + "\n";

    for (i = 0; i < numWorkers; i++) {
        pheromone = bipartite[i][tID];
        
        s += "  W" + std::to_string(i + 1) + ": ";
	s += std::to_string(pheromone) + "\n";
    }

    return s;
}

/**
 * Returns a string representation of the cost of a task. 
 * @param tID The task's ID.
 * @return A string representation of the distribution.
 */
std::string HeuristicGraph::showCosts(int tID) const {
    std::string s;
    int i;
    double cost;

    s = "Costos de la tarea " + std::to_string(tID + 1) + "\n";

    for (i = 0; i < numWorkers; i++) {
        cost = G.getCostOf(i + 1, tID + 1);
        
        s += "  W" + std::to_string(i + 1) + ": ";
	s += std::to_string(cost) + "\n";
    }

    return s;
}

/**
 * Returns a string representation of the capacity of a task. 
 * @param tID The task's ID.
 * @return A string representation of the distribution.
 */
std::string HeuristicGraph::showCapacities(int tID) const {
    std::string s;
    int i;
    double capacity;

    s = "Capacidad de la tarea " + std::to_string(tID + 1) + "\n";

    for (i = 0; i < numWorkers; i++) {
        capacity = G.getCapacityOf(i + 1, tID + 1);
        
        s += "  W" + std::to_string(i + 1) + ": ";
	s += std::to_string(capacity) + "\n";
    }

    return s;
}
