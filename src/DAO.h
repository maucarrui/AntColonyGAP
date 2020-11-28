#include <sqlite3.h>
#include <string>

class DAO {
    private:
        sqlite3* DB;
	std::string location;

    public:
	DAO(std::string location);

	int  openDB();
	void closeDB();
	
	Worker getWorkerByID(int ID);
	Task   getTaskByID(int ID);
	double getCapacity(int tID, int wID);
	double getTask(int tID, int wID);
	
}
