#include "gtest/gtest.h"
#include <string>

#ifndef DAO_H
#define DAO_H
#include "../../src/DAO.hpp"
#endif

#ifndef WORKER_H
#define WORKER_H
#include "../../src/Worker.hpp"
#endif

class DAOTest : public ::testing::Test {
    protected:
        virtual void setUp() {
	}
        
        virtual void TearDown() {
	}
};

TEST_F(DAOTest, getWorkerByID) {
    DAO dao = DAO("../../sql/database.db");
    dao.openDB();

    Worker test1 = dao.getWorkerByID(22);
    Worker test2 = dao.getWorkerByID(70);
    Worker test3 = dao.getWorkerByID(94);

    EXPECT_EQ(test1.getName(), "Francisco Adams");
    EXPECT_EQ(test1.getCapacity(), 106.74667483417282);

    EXPECT_EQ(test2.getName(), "Rosa Rubio");
    EXPECT_EQ(test2.getCapacity(), 99.81386912462163);

    EXPECT_EQ(test3.getName(), "Juan Carlos Williams");
    EXPECT_EQ(test3.getCapacity(), 41.818680153786914);
    
    dao.closeDB();
}

TEST_F(DAOTest, getTaskByID) {
    DAO dao = DAO("../../sql/database.db");
    dao.openDB();

    Task test1 = dao.getTaskByID(450);
    Task test2 = dao.getTaskByID(150);
    Task test3 = dao.getTaskByID(250);

    EXPECT_EQ(test1.getID(), 450);
    EXPECT_EQ(test1.getName(), "inventar el ave");

    EXPECT_EQ(test1.getID(), 150);    
    EXPECT_EQ(test2.getName(), "probar la servilleta");

    EXPECT_EQ(test1.getID(), 250);
    EXPECT_EQ(test3.getName(), "odiar la letra");

    dao.closeDB();
}

TEST_F(DAOTest, getCapacity) {
    DAO dao = DAO("../../sql/database.db");
    dao.openDB();

    double test1 = dao.getCapacity(2, 2);
    double test2 = dao.getCapacity(60, 700);
    double test3 = dao.getCapacity(240, 20);

    EXPECT_EQ(test1, 59.1782397305913);
    EXPECT_EQ(test2, 98.3664869129699);
    EXPECT_EQ(test3, 57.3480542264592);
    
    dao.closeDB();
}

TEST_F(DAOTest, getCost) {
    DAO dao = DAO("../../sql/database.db");
    dao.openDB();

    double test1 = dao.getCost(2, 2);
    double test2 = dao.getCost(60, 700);
    double test3 = dao.getCost(240, 20);

    EXPECT_EQ(test1, 102.251829952483);
    EXPECT_EQ(test2, 41.830639735847);
    EXPECT_EQ(test3, 105.230291998992);
    
    dao.closeDB();
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    
    return RUN_ALL_TESTS();
}
