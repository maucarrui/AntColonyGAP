#include "Ant.hpp"

/**
 * Default constructor for an ant.
 */
Ant::Ant() {
    this->foundFood = false;
}

/**
 * The ant explores an edge.
 * @param edge The explored edge.
 */
void Ant::addEdge(std::pair<int, int> edge) {
    int wID, tID;
    wID = edge.first;
    tID = edge.second;

    travelledEdges.push_back(edge);
    solution.addAssignment(wID, tID);
}

/**
 * The and found food.
 */
void Ant::gotFood() {
    this->foundFood = true;
}

/**
 * Returns true if the ant found food, false otherwise.
 * @return True if the ant found food, false otherwise.
 */
bool Ant::didFoundFood() {
    return this->foundFood;
}

std::vector<std::pair<int, int>> Ant::getEdges() {
    return this->travelledEdges;
}

/**
 * Returns an ant to its colony, forgetting its
 * solution.
 */
void Ant::sendToColony() {
    travelledEdges.clear();
    solution.clear();
    foundFood = false;
}

/**
 * Returns the solution found by the ant.
 * @return The solution found by the ant.
 */
Solution Ant::getSolution() {
    return solution;
}
