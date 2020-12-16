#include "Ant.hpp"

/**
 * Default constructor for an ant.
 */
Ant::Ant() {}

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
}

/**
 * Returns the solution found by the ant.
 * @return The solution found by the ant.
 */
Solution Ant::getSolution() {
    return solution;
}
