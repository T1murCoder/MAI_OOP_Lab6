#pragma once

#include "NPCContainer.h"
#include "../factory/NPCFactoryRegistry.h"
#include <memory>
#include <string>

class BattleSubject;
class ConsoleObserver;
class FileObserver;

class DungeonEditor {
private:
    NPCContainer container;
    NPCFactoryRegistry factoryRegistry;
    std::shared_ptr<BattleSubject> battleSubject;
    std::shared_ptr<ConsoleObserver> consoleObserver;
    std::shared_ptr<FileObserver> fileObserver;
    
public:
    DungeonEditor();
    
    void addNPC(const std::string& type, const std::string& name, float x, float y, int health, int damage);
    void removeNPC(const std::string& name);
    
    NPCContainer& getContainer();
    const NPCContainer& getContainer() const;
    
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
    
    int startBattleRounds(float maxDistance, int rounds); 
    void startBattle(float maxDistance);
    
    ~DungeonEditor() = default;
};