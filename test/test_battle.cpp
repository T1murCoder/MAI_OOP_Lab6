#include <gtest/gtest.h>
#include "../include/utils/BattleEngine.h"
#include "../include/observer/BattleSubject.h"
#include "../include/npc/Bear.h"
#include "../include/npc/Werewolf.h"
#include "../include/npc/Bandit.h"
#include "../include/utils/Point.h"
#include <memory>
#include <vector>

class BattleTest : public ::testing::Test {
protected:
    std::shared_ptr<BattleSubject> subject;
    
    void SetUp() override {
        subject = std::make_shared<BattleSubject>();
    }
    
    std::vector<std::unique_ptr<NPC>> createNPCs() {
        std::vector<std::unique_ptr<NPC>> npcs;
        npcs.push_back(std::make_unique<Bear>("Мишка", Point{100.0f, 100.0f}, 100, 30));
        npcs.push_back(std::make_unique<Werewolf>("Волк", Point{120.0f, 120.0f}, 100, 40));
        npcs.push_back(std::make_unique<Bandit>("Грабитель", Point{140.0f, 140.0f}, 100, 35));
        return npcs;
    }
};

TEST_F(BattleTest, BattleEngineCreation) {
    EXPECT_NO_THROW(BattleEngine engine(subject));
}

TEST_F(BattleTest, BattleEngineNullSubject) {
    EXPECT_THROW(BattleEngine engine(nullptr), std::invalid_argument);
}

TEST_F(BattleTest, ConductRoundWithCloseNPCs) {
    BattleEngine engine(subject);
    
    // Создаем NPC очень близко друг к другу, чтобы гарантировать бой
    std::vector<std::unique_ptr<NPC>> npcs;
    npcs.push_back(std::make_unique<Bear>("Мишка", Point{100.0f, 100.0f}, 100, 1000));
    npcs.push_back(std::make_unique<Werewolf>("Волк", Point{105.0f, 105.0f}, 100, 40));
    
    size_t initialSize = npcs.size();
    bool hadDeaths = engine.conductRound(npcs, 100.0f);
    
    // Медведь убивает оборотня - должна быть смерть
    EXPECT_TRUE(hadDeaths);
    EXPECT_LT(npcs.size(), initialSize);
    
    // Должен остаться только медведь
    ASSERT_EQ(npcs.size(), 1);
    EXPECT_EQ(npcs[0]->getType(), NPCType::BEAR);
}

TEST_F(BattleTest, ConductRoundWithFarNPCs) {
    BattleEngine engine(subject);
    std::vector<std::unique_ptr<NPC>> npcs;
    npcs.push_back(std::make_unique<Bear>("Мишка", Point{0.0f, 0.0f}, 100, 30));
    npcs.push_back(std::make_unique<Werewolf>("Волк", Point{500.0f, 500.0f}, 100, 40));
    
    bool hadDeaths = engine.conductRound(npcs, 50.0f);
    
    // Слишком далеко, боев не должно быть
    EXPECT_FALSE(hadDeaths);
    EXPECT_EQ(npcs.size(), 2);
}

TEST_F(BattleTest, ConductRoundsLimited) {
    BattleEngine engine(subject);
    auto npcs = createNPCs();
    
    int completedRounds = engine.conductRounds(npcs, 100.0f, 2);
    
    EXPECT_LE(completedRounds, 2);
    EXPECT_GE(completedRounds, 1);
}

TEST_F(BattleTest, ConductBattleSameType) {
    BattleEngine engine(subject);
    std::vector<std::unique_ptr<NPC>> npcs;
    npcs.push_back(std::make_unique<Bear>("Мишка1", Point{100.0f, 100.0f}, 100, 30));
    npcs.push_back(std::make_unique<Bear>("Мишка2", Point{120.0f, 120.0f}, 100, 30));
    
    size_t initialSize = npcs.size();
    engine.conductBattle(npcs, 100.0f);
    
    // Медведи не убивают друг друга
    EXPECT_EQ(npcs.size(), initialSize);
}

TEST_F(BattleTest, ConductBattleDifferentTypes) {
    BattleEngine engine(subject);
    std::vector<std::unique_ptr<NPC>> npcs;
    npcs.push_back(std::make_unique<Bear>("Мишка", Point{100.0f, 100.0f}, 100, 30));
    npcs.push_back(std::make_unique<Werewolf>("Волк", Point{105.0f, 105.0f}, 100, 40));
    
    engine.conductBattle(npcs, 100.0f);
    
    // Медведь должен убить оборотня
    EXPECT_EQ(npcs.size(), 1);
    EXPECT_EQ(npcs[0]->getType(), NPCType::BEAR);
}

TEST_F(BattleTest, InvalidDistance) {
    BattleEngine engine(subject);
    auto npcs = createNPCs();
    
    EXPECT_THROW(engine.conductRound(npcs, -10.0f), std::invalid_argument);
    EXPECT_THROW(engine.conductRound(npcs, 0.0f), std::invalid_argument);
}

TEST_F(BattleTest, InvalidRounds) {
    BattleEngine engine(subject);
    auto npcs = createNPCs();
    
    EXPECT_THROW(engine.conductRounds(npcs, 100.0f, -1), std::invalid_argument);
    EXPECT_THROW(engine.conductRounds(npcs, 100.0f, 0), std::invalid_argument);
}