#include <gtest/gtest.h>
#include "../include/factory/BearFactory.h"
#include "../include/factory/WerewolfFactory.h"
#include "../include/factory/BanditFactory.h"
#include "../include/factory/NPCFactoryRegistry.h"
#include "../include/npc/Bear.h"
#include "../include/npc/Werewolf.h"
#include "../include/npc/Bandit.h"
#include "../include/utils/Point.h"
#include <sstream>

class FactoryTest : public ::testing::Test {
protected:
    Point pos{100.0f, 200.0f};
};

TEST_F(FactoryTest, BearFactoryCreate) {
    BearFactory factory;
    auto npc = factory.createNPC("Мишка", pos, 100, 10);
    
    ASSERT_NE(npc, nullptr);
    EXPECT_EQ(npc->getName(), "Мишка");
    EXPECT_EQ(npc->getType(), NPCType::BEAR);
    
    Bear* bear = dynamic_cast<Bear*>(npc.get());
    EXPECT_NE(bear, nullptr);
}

TEST_F(FactoryTest, WerewolfFactoryCreate) {
    WerewolfFactory factory;
    auto npc = factory.createNPC("Волк", pos, 80, 15);
    
    ASSERT_NE(npc, nullptr);
    EXPECT_EQ(npc->getName(), "Волк");
    EXPECT_EQ(npc->getType(), NPCType::WEREWOLF);
    
    Werewolf* werewolf = dynamic_cast<Werewolf*>(npc.get());
    EXPECT_NE(werewolf, nullptr);
}

TEST_F(FactoryTest, BanditFactoryCreate) {
    BanditFactory factory;
    auto npc = factory.createNPC("Грабитель", pos, 70, 20);
    
    ASSERT_NE(npc, nullptr);
    EXPECT_EQ(npc->getName(), "Грабитель");
    EXPECT_EQ(npc->getType(), NPCType::BANDIT);
    
    Bandit* bandit = dynamic_cast<Bandit*>(npc.get());
    EXPECT_NE(bandit, nullptr);
}

TEST_F(FactoryTest, BearFactoryLoadFromStream) {
    BearFactory factory;
    std::istringstream iss("Мишка 100.5 200.3 10 100");
    
    auto npc = factory.loadFromFile(iss);
    
    ASSERT_NE(npc, nullptr);
    EXPECT_EQ(npc->getName(), "Мишка");
    EXPECT_FLOAT_EQ(npc->getPosition().getX(), 100.5f);
    EXPECT_FLOAT_EQ(npc->getPosition().getY(), 200.3f);
}

TEST_F(FactoryTest, FactoryRegistryRegister) {
    NPCFactoryRegistry registry;
    
    registry.registerFactory(NPCType::BEAR, std::make_unique<BearFactory>());
    registry.registerFactory(NPCType::WEREWOLF, std::make_unique<WerewolfFactory>());
    registry.registerFactory(NPCType::BANDIT, std::make_unique<BanditFactory>());
    
    // createNPC требует 5 параметров: typeStr, name, position, health, damage
    auto bear = registry.createNPC("Bear", "Мишка", pos, 100, 30);
    EXPECT_EQ(bear->getType(), NPCType::BEAR);
    
    auto werewolf = registry.createNPC("Werewolf", "Волк", pos, 100, 40);
    EXPECT_EQ(werewolf->getType(), NPCType::WEREWOLF);
    
    auto bandit = registry.createNPC("Bandit", "Грабитель", pos, 100, 35);
    EXPECT_EQ(bandit->getType(), NPCType::BANDIT);
}

TEST_F(FactoryTest, FactoryRegistryUnknownType) {
    NPCFactoryRegistry registry;
    registry.registerFactory(NPCType::BEAR, std::make_unique<BearFactory>());
    
    EXPECT_THROW(registry.createNPC("Dragon", "Дракон", pos, 100, 30), std::invalid_argument);
}

TEST_F(FactoryTest, FactoryRegistryLoad) {
    NPCFactoryRegistry registry;
    
    registry.registerFactory(NPCType::BEAR, std::make_unique<BearFactory>());
    registry.registerFactory(NPCType::WEREWOLF, std::make_unique<WerewolfFactory>());
    registry.registerFactory(NPCType::BANDIT, std::make_unique<BanditFactory>());
    
    std::istringstream iss("Bear Мишка 100.0 200.0 100 10");
    auto npc = registry.loadNPC(iss);
    
    ASSERT_NE(npc, nullptr);
    EXPECT_EQ(npc->getType(), NPCType::BEAR);
    EXPECT_EQ(npc->getName(), "Мишка");
}

TEST_F(FactoryTest, FactoryCreateWithCustomStats) {
    BearFactory factory;
    
    // Создаем медведя с кастомными характеристиками через низкоуровневый метод
    auto npc = factory.createNPC("СильныйМишка", pos, 200, 50);
    
    ASSERT_NE(npc, nullptr);
    EXPECT_EQ(npc->getName(), "СильныйМишка");
    EXPECT_EQ(npc->getType(), NPCType::BEAR);
}

TEST_F(FactoryTest, FactoryRegistryCreateByEnum) {
    NPCFactoryRegistry registry;
    
    registry.registerFactory(NPCType::BEAR, std::make_unique<BearFactory>());
    registry.registerFactory(NPCType::WEREWOLF, std::make_unique<WerewolfFactory>());
    registry.registerFactory(NPCType::BANDIT, std::make_unique<BanditFactory>());
    
    // Создание через enum
    auto bear = registry.createNPC(NPCType::BEAR, "Мишка", pos, 100, 30);
    EXPECT_EQ(bear->getType(), NPCType::BEAR);
    
    auto werewolf = registry.createNPC(NPCType::WEREWOLF, "Волк", pos, 100, 40);
    EXPECT_EQ(werewolf->getType(), NPCType::WEREWOLF);
    
    auto bandit = registry.createNPC(NPCType::BANDIT, "Грабитель", pos, 100, 35);
    EXPECT_EQ(bandit->getType(), NPCType::BANDIT);
}

TEST_F(FactoryTest, WerewolfFactoryLoadFromStream) {
    WerewolfFactory factory;
    std::istringstream iss("ГрозныйВолк 250.0 350.5 80 30");
    
    auto npc = factory.loadFromFile(iss);
    
    ASSERT_NE(npc, nullptr);
    EXPECT_EQ(npc->getName(), "ГрозныйВолк");
    EXPECT_EQ(npc->getType(), NPCType::WEREWOLF);
    EXPECT_FLOAT_EQ(npc->getPosition().getX(), 250.0f);
    EXPECT_FLOAT_EQ(npc->getPosition().getY(), 350.5f);
}

TEST_F(FactoryTest, BanditFactoryLoadFromStream) {
    BanditFactory factory;
    std::istringstream iss("ХитрыйБандит 150.5 250.3 80 15");
    
    auto npc = factory.loadFromFile(iss);
    
    ASSERT_NE(npc, nullptr);
    EXPECT_EQ(npc->getName(), "ХитрыйБандит");
    EXPECT_EQ(npc->getType(), NPCType::BANDIT);
    EXPECT_FLOAT_EQ(npc->getPosition().getX(), 150.5f);
    EXPECT_FLOAT_EQ(npc->getPosition().getY(), 250.3f);
}