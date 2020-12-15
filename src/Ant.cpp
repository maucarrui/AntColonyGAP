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
    travelledEdges.push_back(edge);
}

/**
 * Returns an ant to its colony, forgetting its
 * solution.
 */
void Ant::sendToColony() {
    travelledEdges.clear();
}

/**
 * Returns the solution found by the ant.
 * @return The solution found by the ant.
 */
Solution Ant::getSolution() {
    return Solution(travelledEdges);
}
