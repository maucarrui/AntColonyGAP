#include "DAO.hpp"

/**
 * Default constructor.
 */
DAO::DAO() {}

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
    const char* c_location = location.c_str();
    int exit = sqlite3_open(c_location, &DB);
    
    if (exit) {
        // std::cerr << "Error at opening DB: " << sqlite3_errmsg(DB) << std::endl;
	return -1;
    } else {
        // std::cout << "Opened database successfully" << std::endl;
        return 0;
    }
}

/**
 * Closes the connection with the database.
 */
void DAO::closeDB() {
    sqlite3_close(DB);
    // std::cout << "Closed database connection successfully." << std::endl;
}

/**
 * Returns a worker given its ID.
 * @param ID The worker's ID.
 * @return The found worker.
 */
Worker DAO::getWorkerByID(int ID) {
    // Worker's attributes.
    std::string name;
    double capacity;

    // SQL query;
    std::string query;
    query  = "SELECT * FROM trabajadores WHERE id = ";
    query += std::to_string(ID);

    const char* c_query = query.c_str();

    // Execute the query.
    sqlite3_stmt * stmt;
    sqlite3_prepare(DB, c_query, -1, &stmt, NULL);

    sqlite3_step(stmt);
    
    name     = std::string( (char *) sqlite3_column_text(stmt, 1) );
    capacity = sqlite3_column_double(stmt, 2);

    return Worker(ID, name, capacity);
}

/**
 * Returns a task given its ID.
 * @param ID The task's ID.
 * @return The found task.
 */
Task DAO::getTaskByID(int ID) {
    // Task's attributes.
    std::string name;

    // SQL query;
    std::string query;
    query  = "SELECT * FROM tareas WHERE id = ";
    query += std::to_string(ID);

    const char* c_query = query.c_str();

    // Execute the query.
    sqlite3_stmt * stmt;
    sqlite3_prepare(DB, c_query, -1, &stmt, NULL);

    sqlite3_step(stmt);
    
    name     = std::string( (char *) sqlite3_column_text(stmt, 1) );

    return Task(ID, name);
}

/**
 * Returns the worker's capacity of doing a task.
 * @param  wID The worker's ID.
 * @param  tID The task's ID.
 * @return The worker's capacity of doing a task.
 */
double DAO::getCapacity(int wID, int tID) {
    // SQL query;
    std::string query;
    query  = "SELECT * FROM capacidades WHERE id_tarea = ";
    query += std::to_string(tID);
    query += " AND id_trabajador = ";
    query += std::to_string(wID);

    const char* c_query = query.c_str();

    // Execute the query.
    sqlite3_stmt * stmt;
    sqlite3_prepare(DB, c_query, -1, &stmt, NULL);

    sqlite3_step(stmt);
    
    double capacity = sqlite3_column_double(stmt, 2);

    return capacity;
}

/**
 * Returns the cost of the completion of a task by a worker.
 * @param  wID The worker's ID.
 * @param  tID The task's ID.
 * @return The cost of the completion of a task by a worker.
 */
double DAO::getCost(int wID, int tID) {
    // SQL query;
    std::string query;
    query  = "SELECT * FROM costos WHERE id_tarea = ";
    query += std::to_string(tID);
    query += " AND id_trabajador = ";
    query += std::to_string(wID);

    const char* c_query = query.c_str();

    // Execute the query.
    sqlite3_stmt * stmt;
    sqlite3_prepare(DB, c_query, -1, &stmt, NULL);

    sqlite3_step(stmt);
    
    double cost = sqlite3_column_double(stmt, 2);

    return cost;
}

/**
 * Returns all the current workers in the database.
 * @return A vector containing all the workers which are in the DB.
 */
std::vector<Worker> DAO::getWorkers() {
    // Vector of workers.
    std::vector<Worker> workers;
  
    // Worker's attributes.
    int ID;
    std::string name;
    double capacity;

    // SQL query;
    std::string query;
    query = "SELECT * FROM trabajadores";

    const char* c_query = query.c_str();

    // Execute the query.
    sqlite3_stmt * stmt;
    sqlite3_prepare(DB, c_query, -1, &stmt, NULL);

    sqlite3_step(stmt);

    while (sqlite3_column_int(stmt, 0)) {
        ID       = sqlite3_column_int(stmt, 0);
        name     = std::string( (char *) sqlite3_column_text(stmt, 1) );
	capacity = sqlite3_column_double(stmt, 2);
	
	Worker w = Worker(ID, name, capacity);
	workers.push_back(w);

	sqlite3_step(stmt);
    }

    return workers;
}

/**
 * Returns all the current tasks in the database.
 * @return A vector containing all the tasks which are in the DB.
 */
std::vector<Task> DAO::getTasks() {
    // Vector of tasks.
    std::vector<Task> tasks;
  
    // Task's attributes.
    int ID;
    std::string name;

    // SQL query;
    std::string query;
    query = "SELECT * FROM tareas";

    const char* c_query = query.c_str();

    // Execute the query.
    sqlite3_stmt * stmt;
    sqlite3_prepare(DB, c_query, -1, &stmt, NULL);

    sqlite3_step(stmt);

    while (sqlite3_column_int(stmt, 0)) {
        ID       = sqlite3_column_int(stmt, 0);
        name     = std::string( (char *) sqlite3_column_text(stmt, 1) );
	
	Task t = Task(ID, name);
	tasks.push_back(t);
	
	sqlite3_step(stmt);
    }

    return tasks;
}
