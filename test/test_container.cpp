#include <gtest/gtest.h>
#include "../include/editor/NPCContainer.h"
#include "../include/npc/Bear.h"
#include "../include/npc/Werewolf.h"
#include "../include/npc/Bandit.h"
#include "../include/utils/Point.h"

class ContainerTest : public ::testing::Test {
protected:
    NPCContainer container;
    Point pos1{100.0f, 200.0f};
    Point pos2{150.0f, 250.0f};
    Point pos3{200.0f, 300.0f};
};

TEST_F(ContainerTest, InitiallyEmpty) {
    EXPECT_EQ(container.size(), 0);
}

TEST_F(ContainerTest, AddNPC) {
    auto bear = std::make_unique<Bear>("Мишка", pos1, 100, 30);
    container.add(std::move(bear));
    
    EXPECT_EQ(container.size(), 1);
}

TEST_F(ContainerTest, AddMultipleNPCs) {
    container.add(std::make_unique<Bear>("Мишка", pos1, 100, 30));
    container.add(std::make_unique<Werewolf>("Волк", pos2, 100, 40));
    container.add(std::make_unique<Bandit>("Грабитель", pos3, 100, 35));
    
    EXPECT_EQ(container.size(), 3);
}

TEST_F(ContainerTest, AddNullNPC) {
    EXPECT_THROW(container.add(nullptr), std::invalid_argument);
}

TEST_F(ContainerTest, AddDuplicateName) {
    container.add(std::make_unique<Bear>("Мишка", pos1, 100, 30));
    
    EXPECT_THROW(
        container.add(std::make_unique<Werewolf>("Мишка", pos2, 100, 40)),
        std::invalid_argument
    );
}

TEST_F(ContainerTest, HasName) {
    container.add(std::make_unique<Bear>("Мишка", pos1, 100, 30));
    
    EXPECT_TRUE(container.hasName("Мишка"));
    EXPECT_FALSE(container.hasName("Волк"));
}

TEST_F(ContainerTest, RemoveExistingNPC) {
    container.add(std::make_unique<Bear>("Мишка", pos1, 100, 30));
    container.add(std::make_unique<Werewolf>("Волк", pos2, 100, 40));
    
    EXPECT_EQ(container.size(), 2);
    
    container.remove("Мишка");
    
    EXPECT_EQ(container.size(), 1);
    EXPECT_FALSE(container.hasName("Мишка"));
    EXPECT_TRUE(container.hasName("Волк"));
}

TEST_F(ContainerTest, RemoveNonExistingNPC) {
    container.add(std::make_unique<Bear>("Мишка", pos1, 100, 30));
    
    // Не должно бросать исключение
    container.remove("НеСуществует");
    
    EXPECT_EQ(container.size(), 1);
}

TEST_F(ContainerTest, Clear) {
    container.add(std::make_unique<Bear>("Мишка", pos1, 100, 30));
    container.add(std::make_unique<Werewolf>("Волк", pos2, 100, 40));
    container.add(std::make_unique<Bandit>("Грабитель", pos3, 100, 35));
    
    EXPECT_EQ(container.size(), 3);
    
    container.clear();
    
    EXPECT_EQ(container.size(), 0);
}

TEST_F(ContainerTest, GetAll) {
    container.add(std::make_unique<Bear>("Мишка", pos1, 100, 30));
    container.add(std::make_unique<Werewolf>("Волк", pos2, 100, 40));
    
    auto& npcs = container.getAll();
    
    EXPECT_EQ(npcs.size(), 2);
}