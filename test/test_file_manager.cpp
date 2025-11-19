#include <gtest/gtest.h>
#include "../include/utils/FileManager.h"
#include "../include/factory/NPCFactoryRegistry.h"
#include "../include/factory/BearFactory.h"
#include "../include/factory/WerewolfFactory.h"
#include "../include/factory/BanditFactory.h"
#include "../include/npc/Bear.h"
#include "../include/npc/Werewolf.h"
#include "../include/npc/Bandit.h"
#include "../include/utils/Point.h"
#include <fstream>
#include <filesystem>

class FileManagerTest : public ::testing::Test {
protected:
    NPCFactoryRegistry registry;
    std::string testFile = "test_npcs.txt";
    
    void SetUp() override {
        registry.registerFactory(NPCType::BEAR, std::make_unique<BearFactory>());
        registry.registerFactory(NPCType::WEREWOLF, std::make_unique<WerewolfFactory>());
        registry.registerFactory(NPCType::BANDIT, std::make_unique<BanditFactory>());
    }
    
    void TearDown() override {
        if (std::filesystem::exists(testFile)) {
            std::filesystem::remove(testFile);
        }
    }
    
    std::vector<std::unique_ptr<NPC>> createTestNPCs() {
        std::vector<std::unique_ptr<NPC>> npcs;
        npcs.push_back(std::make_unique<Bear>("Мишка", Point{100.0f, 200.0f}, 100, 30));
        npcs.push_back(std::make_unique<Werewolf>("Волк", Point{150.0f, 250.0f}, 100, 40));
        npcs.push_back(std::make_unique<Bandit>("Грабитель", Point{200.0f, 300.0f}, 100, 35));
        return npcs;
    }
};

TEST_F(FileManagerTest, SaveToFile) {
    FileManager manager(registry);
    auto npcs = createTestNPCs();
    
    EXPECT_NO_THROW(manager.save(npcs, testFile));
    EXPECT_TRUE(std::filesystem::exists(testFile));
}

TEST_F(FileManagerTest, LoadFromFile) {
    FileManager manager(registry);
    auto npcs = createTestNPCs();
    
    manager.save(npcs, testFile);
    
    auto loadedNPCs = manager.load(testFile);
    
    EXPECT_EQ(loadedNPCs.size(), 3);
}

TEST_F(FileManagerTest, SaveAndLoadPreservesData) {
    FileManager manager(registry);
    auto npcs = createTestNPCs();
    
    manager.save(npcs, testFile);
    auto loadedNPCs = manager.load(testFile);
    
    ASSERT_EQ(loadedNPCs.size(), 3);
    
    EXPECT_EQ(loadedNPCs[0]->getName(), "Мишка");
    EXPECT_EQ(loadedNPCs[0]->getType(), NPCType::BEAR);
    EXPECT_FLOAT_EQ(loadedNPCs[0]->getPosition().getX(), 100.0f);
    EXPECT_FLOAT_EQ(loadedNPCs[0]->getPosition().getY(), 200.0f);
    
    EXPECT_EQ(loadedNPCs[1]->getName(), "Волк");
    EXPECT_EQ(loadedNPCs[1]->getType(), NPCType::WEREWOLF);
    
    EXPECT_EQ(loadedNPCs[2]->getName(), "Грабитель");
    EXPECT_EQ(loadedNPCs[2]->getType(), NPCType::BANDIT);
}

TEST_F(FileManagerTest, LoadNonExistentFile) {
    FileManager manager(registry);
    
    EXPECT_THROW(manager.load("non_existent_file.txt"), std::runtime_error);
}

TEST_F(FileManagerTest, LoadCorruptedFile) {
    // Создаем файл с некорректными данными
    std::ofstream file(testFile);
    file << "InvalidType InvalidName abc def\n";
    file.close();
    
    FileManager manager(registry);
    
    EXPECT_THROW(manager.load(testFile), std::runtime_error);
}

TEST_F(FileManagerTest, LoadEmptyFile) {
    // Создаем пустой файл
    std::ofstream file(testFile);
    file.close();
    
    FileManager manager(registry);
    auto npcs = manager.load(testFile);
    
    EXPECT_EQ(npcs.size(), 0);
}