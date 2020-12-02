#include <string>

class Worker {
    private:
        int ID;
        std::string name;
	double capacity;

    public:
	Worker(int ID, std::string name, double capacity);
	
        int getID();
	std::string getName();
	double getCapacity();
};
