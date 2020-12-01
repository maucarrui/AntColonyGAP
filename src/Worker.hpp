#include <string>

class Worker {
    private:
        std::string name;
	double capacity;

    public:
	Worker(std::string name, double capacity);
	
	std::string getName();
	double getCapacity();
};
