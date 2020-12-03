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

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
