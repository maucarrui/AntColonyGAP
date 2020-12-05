#include "Solution.hpp"

/**
 * Constructor for a solution.
 * A solution consists in the edges of the 
 * bipartite graph, its cost, its capacity and 
 * if it's feasible or not.
 * @param edges The edges of the bipartite graph.
 */
Solution::Solution(std::vector<std::pair<int, int>> edges) {
    this->edges      = edges;
    this->capacity   = 0;
    this->cost       = 0;
    this->isFeasible = false;
}

/**
 * Returns the capacity of the solution.
 * @return The capacity of the solution.
 */
double Solution::getCapacity() {
    return this->capacity;
}

/**
 * Returns the cost of the solution.
 * @return The cost of the solution.
 */
double Solution::getCost() {
    return this->cost;
}

/**
 * Returns the feasibility of the solution.
 * @return The feasibility of the solution.
 */
bool Solution::getFeasibility() {
    return this->isFeasible;
}

/**
 * Sets the capacity of the solution.
 * @param The new capacity of the solution.
 */
void Solution::setCapacity(double newCapacity) {
    this->capacity = newCapacity;
}

/**
 * Sets the cost of the solution.
 * @param The new cost of the solution.
 */
void Solution::setCost(double newCost) {
    this->cost = newCost;
}

/**
 * Returns a set of edges corresponding to a
 * new solution.
 * A new solution is generated selecting a 
 * a random task and assigning another worker to 
 * it.
 */
std::vector<std::pair<int, int>> Solution::getRandomNeighbor() {
    int newWorker, oldWorker;
    int numTasks = edges.size();
    
    // Select random task.
    int randTask = rand() % numTasks;

    oldWorker = newWorker = edges[randTask].first;

    while (oldWorker == newWorker)
        newWorker = rand() % 500 + 1;

    // Create the neighbor
    std::vector<std::pair<int, int>> neighbor;
    neighbor = edges;
    neighbor[randTask].first = newWorker;

    return neighbor;
}
