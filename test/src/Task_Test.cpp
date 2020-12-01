#include "gtest/gtest.h"
#include <string>

#ifndef TASK_H
#define TASK_H
#include "../../src/Task.hpp"
#endif

class TaskTest : public ::testing::Test {
    protected:
        virtual void setUp() {
	}

        virtual void TearDown() {
	}
};

TEST_F(TaskTest, getID) {
    Task t1 = Task(0, "NULL");
    Task t2 = Task(1, "NULL");
    Task t3 = Task(2, "NULL");

    EXPECT_EQ(0, t1.getID());
    EXPECT_EQ(1, t2.getID());
    EXPECT_EQ(2, t3.getID());
}

TEST_F(TaskTest, getName) {
    Task t1 = Task(0, "Example 1");
    Task t2 = Task(1, "Example 2");
    Task t3 = Task(2, "Example 3");

    EXPECT_EQ("Example 1", t1.getName());
    EXPECT_EQ("Example 2", t2.getName());
    EXPECT_EQ("Example 3", t3.getName());    
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
