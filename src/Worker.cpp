#include "Worker.h"

/**
 * Constructor for a worker.
 * A worker has a name and its capacity to complete
 * tasks.
 *
 * @param name     The name of the worker.
 * @param capacity The capacity of the worker.
 */
Worker::Worker(std::string name, double capacity) {
    this->name     = name;
    this->capacity = capacity;
}

/**
 * Returns the worker's name.
 * @return The worker's name.
 */
std::string Worker::getName() {
    return this->name;
}

/**
 * Returns the worker's capacity.
 * @return The worker's capacity.
 */
double Worker::getCapacity() {
    return this->capacity;
}
