#include "DAO.h"

/**
 * Constructor for the DAO (Database Access Object).
 */
DAO::DAO(std::string location) {
    this->location = location;
}

/**
 * Opens a connection with the database.
 * @return The status of the connection.
 */
int DAO::openDB() {
    return 0;
}

/**
 * Closes the connection with the database.
 */
void DAO::closeDB() {
    return;
}

/**
 * Returns a worker given its ID.
 * @param ID The worker's ID.
 * @return The found worker.
 */
Worker DAO::getWorkerByID(int ID) {
    return 0;
}

/**
 * Returns a task given its ID.
 * @param ID The task's ID.
 * @return The found task.
 */
Worker DAO::getWorkerByID(int ID) {
    return 0;
}

/**
 * Returns the worker's capacity of doing a task.
 * @param  wID The worker's ID.
 * @param  tID The task's ID.
 * @return The worker's capacity of doing a task.
 */
double DAO::getCapacity(int wID, int tID) {
    return 0;
}

/**
 * Returns the cost of the completion of a task by a worker.
 * @param  wID The worker's ID.
 * @param  tID The task's ID.
 * @return The cost of the completion of a task by a worker.
 */
double DAO::getCost(int wID, int tID) {
    return 0;
}
