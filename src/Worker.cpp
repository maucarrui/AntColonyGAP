#include "Worker.hpp"

/**
 * Default constructor.
 */
Worker::Worker() {}

/**
 * Constructor for a worker.
 * A worker has a name and its capacity to complete
 * tasks.
 *
 * @param ID       The ID of the worker.
 * @param name     The name of the worker.
 * @param capacity The capacity of the worker.
 */
Worker::Worker(int ID, std::string name, double capacity) {
    this->ID       = ID;
    this->name     = name;
    this->capacity = capacity;
}

/**
 * Returns the worker's ID.
 * @return The worker's ID.
 */
int  Worker::getID() const {
    return this->ID;
}


/**
 * Returns the worker's name.
 * @return The worker's name.
 */
std::string Worker::getName() const {
    return this->name;
}

/**
 * Returns the worker's capacity.
 * @return The worker's capacity.
 */
double Worker::getCapacity() const {
    return this->capacity;
}
