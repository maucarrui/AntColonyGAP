#include "gtest/gtest.h"
#include <string>

#ifndef GRAPH_H
#define GRAPH_H
#include "../../src/Graph.hpp"
#endif

#ifndef DAO_H
#define DAO_H
#include "../../src/DAO.hpp"
#endif

#ifndef WORKER_H
#define WORKER_H
#include "../../src/Worker.hpp"
#endif

#ifndef TASK_H
#define TASK_H
#include "../../src/Task.hpp"
#endif

#ifndef SOLUTION_H
#define SOLUTION_H
#include "../../src/Solution.hpp"
#endif

class GRAPHTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
        }

        virtual void TearDown() {
	}
};

TEST_F(GRAPHTest, constructor) {
    DAO dao = DAO("../sql/database.db");
    dao.openDB();

    std::vector<Worker> workers = dao.getWorkers();
    std::vector<Task>   tasks   = dao.getTasks();

    Graph G = Graph(workers, tasks, dao);

    EXPECT_EQ(500, G.getNumWorkers());
    EXPECT_EQ(1000, G.getNumTasks());
    EXPECT_EQ(500 * 1000, G.getNumEdges());
}

TEST_F(GRAPHTest, getCapacityOf) {
    DAO dao = DAO("../sql/database.db");
    dao.openDB();

    std::vector<Worker> workers = dao.getWorkers();
    std::vector<Task>   tasks   = dao.getTasks();

    Graph G = Graph(workers, tasks, dao);

    double test1 = dao.getCapacity(2, 2);
    double test2 = dao.getCapacity(60, 700);
    double test3 = dao.getCapacity(240, 20);
    
    double supp_test1 = G.getCapacityOf(2, 2);
    double supp_test2 = G.getCapacityOf(60, 700);
    double supp_test3 = G.getCapacityOf(240, 20);

    EXPECT_EQ(test1, supp_test1);
    EXPECT_EQ(test2, supp_test2);
    EXPECT_EQ(test3, supp_test3);
}

TEST_F(GRAPHTest, getCostOf) {
    DAO dao = DAO("../sql/database.db");
    dao.openDB();

    std::vector<Worker> workers = dao.getWorkers();
    std::vector<Task>   tasks   = dao.getTasks();

    Graph G = Graph(workers, tasks, dao);

    double test1 = dao.getCost(2, 2);
    double test2 = dao.getCost(60, 700);
    double test3 = dao.getCost(240, 20);
    
    double supp_test1 = G.getCostOf(2, 2);
    double supp_test2 = G.getCostOf(60, 700);
    double supp_test3 = G.getCostOf(240, 20);

    EXPECT_EQ(test1, supp_test1);
    EXPECT_EQ(test2, supp_test2);
    EXPECT_EQ(test3, supp_test3);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
