#include <string>

class Worker {
    private:
        int ID;
        std::string name;
	double capacity;

    public:
        Worker();
	Worker(int ID, std::string name, double capacity);
	
        int getID() const;
	std::string getName() const;
	double getCapacity() const;
};
