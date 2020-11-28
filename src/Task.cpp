/**
 * Constructor for a task.
 * A task has an ID and a name.
 *
 * @param ID   The task's ID.
 * @param name The task's name.
 */
Task::Task(int ID, std::string name) {
    this->ID   = ID;
    this->name = name;
}

/**
 * Returns the task's ID.
 * @return The task's ID.
 */
int Task::getID() {
   return this->ID;
}

/**
 * Returns the task's name.
 * @return The task's name.
 */
std::string Task::getName() {
   return this->name; 
}
