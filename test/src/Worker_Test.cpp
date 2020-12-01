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


TEST_F(WorkerTest, getName) {
    std::string name1 = "Steve";
    std::string name2 = "Carlos";
    std::string name3 = "Luigi";

    Worker worker1 = Worker(name1, 0);
    Worker worker2 = Worker(name2, 0);
    Worker worker3 = Worker(name3, 0);

    EXPECT_EQ(name1, worker1.getName());
    EXPECT_EQ(name2, worker2.getName());
    EXPECT_EQ(name3, worker3.getName());
}

TEST_F(WorkerTest, getCapacity) {
    int capacity1 = 4.0;
    int capacity2 = 0;
    int capacity3 = 10;

    Worker worker1 = Worker("Steve", capacity1);
    Worker worker2 = Worker("Steve", capacity2);
    Worker worker3 = Worker("Steve", capacity3);

    EXPECT_EQ(capacity1, worker1.getCapacity());
    EXPECT_EQ(capacity2, worker2.getCapacity());
    EXPECT_EQ(capacity3, worker3.getCapacity());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
