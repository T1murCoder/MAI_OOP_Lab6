#include <gtest/gtest.h>
#include "../include/npc/Bear.h"
#include "../include/npc/Werewolf.h"
#include "../include/npc/Bandit.h"
#include "../include/utils/Point.h"

class NPCTest : public ::testing::Test {
protected:
    Point pos{100.0f, 200.0f};
};

TEST_F(NPCTest, BearCreation) {
    Bear bear("Мишка", pos, 100, 30);
    
    EXPECT_EQ(bear.getName(), "Мишка");
    EXPECT_EQ(bear.getType(), NPCType::BEAR);
    EXPECT_EQ(bear.getTypeString(), "Bear");
    EXPECT_TRUE(bear.getPosition() == pos);
    EXPECT_TRUE(bear.isAlive());
}

TEST_F(NPCTest, WerewolfCreation) {
    Werewolf werewolf("Волк", pos, 100, 40);
    
    EXPECT_EQ(werewolf.getName(), "Волк");
    EXPECT_EQ(werewolf.getType(), NPCType::WEREWOLF);
    EXPECT_EQ(werewolf.getTypeString(), "Werewolf");
    EXPECT_TRUE(werewolf.getPosition() == pos);
    EXPECT_TRUE(werewolf.isAlive());
}

TEST_F(NPCTest, BanditCreation) {
    Bandit bandit("Грабитель", pos, 100, 35);
    
    EXPECT_EQ(bandit.getName(), "Грабитель");
    EXPECT_EQ(bandit.getType(), NPCType::BANDIT);
    EXPECT_EQ(bandit.getTypeString(), "Bandit");
    EXPECT_TRUE(bandit.getPosition() == pos);
    EXPECT_TRUE(bandit.isAlive());
}

TEST_F(NPCTest, NPCDeath) {
    Bear bear("Мишка", pos, 100, 30);
    
    EXPECT_TRUE(bear.isAlive());
    
    // Наносим урон больше, чем здоровье
    bear.takeDamage(150);
    
    EXPECT_FALSE(bear.isAlive());
}

TEST_F(NPCTest, NPCTakeDamage) {
    Bear bear("Мишка", pos, 100, 30);
    
    EXPECT_TRUE(bear.isAlive());
    
    // Наносим урон меньше здоровья
    bear.takeDamage(50);
    EXPECT_TRUE(bear.isAlive());
    
    // Наносим урон, который убьет
    bear.takeDamage(60);
    EXPECT_FALSE(bear.isAlive());
}

TEST_F(NPCTest, NPCTypeToString) {
    EXPECT_EQ(npcTypeToString(NPCType::BEAR), "Bear");
    EXPECT_EQ(npcTypeToString(NPCType::WEREWOLF), "Werewolf");
    EXPECT_EQ(npcTypeToString(NPCType::BANDIT), "Bandit");
}

TEST_F(NPCTest, StringToNPCType) {
    EXPECT_EQ(stringToNPCType("Bear"), NPCType::BEAR);
    EXPECT_EQ(stringToNPCType("Werewolf"), NPCType::WEREWOLF);
    EXPECT_EQ(stringToNPCType("Bandit"), NPCType::BANDIT);
    
    EXPECT_THROW(stringToNPCType("Unknown"), std::invalid_argument);
    EXPECT_THROW(stringToNPCType("bear"), std::invalid_argument);
}

TEST_F(NPCTest, BearDefaultStats) {
    Bear bear("Мишка", pos, 100, 30);
    
    EXPECT_EQ(bear.getType(), NPCType::BEAR);
}

TEST_F(NPCTest, WerewolfDefaultStats) {
    Werewolf werewolf("Волк", pos, 100, 40);
    
    EXPECT_EQ(werewolf.getType(), NPCType::WEREWOLF);
}

TEST_F(NPCTest, BanditDefaultStats) {
    Bandit bandit("Грабитель", pos, 100, 35);
    
    EXPECT_EQ(bandit.getType(), NPCType::BANDIT);
}