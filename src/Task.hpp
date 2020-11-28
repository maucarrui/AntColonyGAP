#include <string>

class Task {
    private:
        int ID;
        std::string name;

    public:
	Task(int ID, std::string name);
	
        int getID();
	std::string getName();
}
