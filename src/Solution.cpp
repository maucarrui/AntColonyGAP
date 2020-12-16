#include "Solution.hpp"

/**
 * Constructor for a solution.
 * A solution consists in the edges of the 
 * bipartite graph, its cost, its capacity and 
 * if it's feasible or not.
 * @param edges The edges of the bipartite graph.
 */
Solution::Solution() {
    this->cost = 0;
    this->isFeasible = false;
}

/**
 * Adds an assignment to the solution.
 * @param wID The worker's ID.
 * @param tID The task's ID.
 */
void Solution::addAssignment(int wID, int tID) {
    std::map<int, std::vector<int>>::iterator it;
    it = assignments.find(wID);
    if (it == assignments.end())
        assignments[wID] =  std::vector<int> { tID };
    else
        it->second.push_back(tID);
}

/**
 * Returns the edges of the solution.
 * @return The edges of the solution.
 */
std::map<int, std::vector<int>> Solution::getAssignments() {
    return this->assignments;
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
 * @param newCapacity The new capacity of the solution.
 */
void Solution::setCapacity(double newCapacity) {
    this->capacity = newCapacity;
}

/**
 * Sets the cost of the solution.
 * @param newCost The new cost of the solution.
 */
void Solution::setCost(double newCost) {
    this->cost = newCost;
}

/**
 * Sets the feasibility of the solution.
 * @param status The status of the solution.
 */
void Solution::setFeasibility(bool status) {
    this->isFeasible = status;
}


/**
 * Resets the status of the solution.
 */
void Solution::clear() {
    this->cost       = 0;
    this->isFeasible = false;
    this->assignments.clear();
}

/**
 * Returns a string representation of the solution.
 * @return A string representation of the solution.
 */
std::string Solution::toString() {
    std::map<int, std::vector<int>>::iterator it;
    std::string s;
    int numTasks;

    s  = "Cost: " + std::to_string(cost) + "\n";
    s += "Feasible: ";

    if (isFeasible)
        s += "TRUE\n";
    else
        s += "FALSE\n";

    s += "Group Assignment: \n";
    
    for (it = assignments.begin(); it != assignments.end(); it++) {
        s        += "  " + std::to_string(it->first) + ": {";
	numTasks  = it->second.size();
 
	for (int i = 0; i < numTasks; i++) {
	    if (i == (numTasks - 1))
	        s += std::to_string(it->second[i]) + "}\n";
	    else
	        s += std::to_string(it->second[i]) + ", ";
	}
    }

    return s;
}
