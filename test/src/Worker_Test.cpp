#include "gtest/gtest.h"
#include <string>

#ifndef WORKER_H
#define WORKER_H
#include "../../src/Worker.hpp"
#endif

class WorkerTest : public ::testing::Test {
    protected:
        virtual void setUp() {
	}

        virtual void TearDown() {
	}
};

TEST_F(WorkerTest, getID) {
    Worker worker1 = Worker(1, "NULL", 0);
    Worker worker2 = Worker(2, "NULL", 0);
    Worker worker3 = Worker(3, "NULL", 0);

    EXPECT_EQ(1, worker1.getID());
    EXPECT_EQ(2, worker2.getID());
    EXPECT_EQ(3, worker3.getID());
}

TEST_F(WorkerTest, getName) {
    std::string name1 = "Steve";
    std::string name2 = "Carlos";
    std::string name3 = "Luigi";

    Worker worker1 = Worker(1, name1, 0);
    Worker worker2 = Worker(2, name2, 0);
    Worker worker3 = Worker(3, name3, 0);

    EXPECT_EQ(name1, worker1.getName());
    EXPECT_EQ(name2, worker2.getName());
    EXPECT_EQ(name3, worker3.getName());
}

TEST_F(WorkerTest, getCapacity) {
    int capacity1 = 4.0;
    int capacity2 = 0;
    int capacity3 = 10;

    Worker worker1 = Worker(1, "Steve", capacity1);
    Worker worker2 = Worker(2, "Steve", capacity2);
    Worker worker3 = Worker(3, "Steve", capacity3);

    EXPECT_EQ(capacity1, worker1.getCapacity());
    EXPECT_EQ(capacity2, worker2.getCapacity());
    EXPECT_EQ(capacity3, worker3.getCapacity());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
