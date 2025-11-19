#include "../../include/editor/DungeonEditor.h"
#include "../../include/factory/BearFactory.h"
#include "../../include/factory/WerewolfFactory.h"
#include "../../include/factory/BanditFactory.h"
#include "../../include/observer/BattleSubject.h"
#include "../../include/observer/ConsoleObserver.h"
#include "../../include/observer/FileObserver.h"
#include "../../include/utils/FileManager.h"
#include "../../include/utils/BattleEngine.h"
#include "../../include/npc/NPC.h"
#include "../../include/utils/Point.h"
#include <stdexcept>

DungeonEditor::DungeonEditor() {
    // Регистрируем фабрики для всех типов NPC
    factoryRegistry.registerFactory(NPCType::BEAR, 
                                   std::make_unique<BearFactory>());
    factoryRegistry.registerFactory(NPCType::WEREWOLF, 
                                   std::make_unique<WerewolfFactory>());
    factoryRegistry.registerFactory(NPCType::BANDIT, 
                                   std::make_unique<BanditFactory>());
    
    battleSubject = std::make_shared<BattleSubject>();
    
    consoleObserver = std::make_shared<ConsoleObserver>();
    fileObserver = std::make_shared<FileObserver>("log.txt");
    
    battleSubject->attach(consoleObserver);
    battleSubject->attach(fileObserver);
}

void DungeonEditor::addNPC(const std::string& type, 
                           const std::string& name, 
                           float x, float y, int health, int damage) {
    Point position(x, y);
    if (!position.isValid()) {
        throw std::invalid_argument("Координаты должны быть в диапазоне [0, 500]");
    }
    
    if (container.hasName(name)) {
        throw std::invalid_argument("NPC с именем \"" + name + "\" уже существует");
    }
    
    auto npc = factoryRegistry.createNPC(type, name, position, health, damage);
    container.add(std::move(npc));
}

void DungeonEditor::removeNPC(const std::string& name) {
    if (!container.hasName(name)) {
        throw std::invalid_argument("NPC с именем \"" + name + "\" не найден");
    }
    container.remove(name);
}

NPCContainer& DungeonEditor::getContainer() {
    return container;
}

const NPCContainer& DungeonEditor::getContainer() const {
    return container;
}

void DungeonEditor::saveToFile(const std::string& filename) {
    if (filename.empty()) {
        throw std::invalid_argument("Имя файла не может быть пустым");
    }
    
    FileManager fileManager(factoryRegistry);
    fileManager.save(container.getAll(), filename);
}

void DungeonEditor::loadFromFile(const std::string& filename) {
    if (filename.empty()) {
        throw std::invalid_argument("Имя файла не может быть пустым");
    }
    
    FileManager fileManager(factoryRegistry);
    auto npcs = fileManager.load(filename);
    
    for (auto& npc : npcs) {
        if (container.hasName(npc->getName())) {
            continue;
        }
        container.add(std::move(npc));
    }
}

int DungeonEditor::startBattleRounds(float maxDistance, int rounds) {
    if (maxDistance <= 0) {
        throw std::invalid_argument("Дистанция должна быть положительной");
    }
    
    if (rounds <= 0) {
        throw std::invalid_argument("Количество раундов должно быть положительным");
    }
    
    BattleEngine engine(battleSubject);
    return engine.conductRounds(container.getAll(), maxDistance, rounds);
}

void DungeonEditor::startBattle(float maxDistance) {
    if (maxDistance <= 0) {
        throw std::invalid_argument("Дистанция должна быть положительной");
    }
    
    if (container.size() == 0) {
        throw std::runtime_error("В подземелье нет NPC для боя");
    }
    
    BattleEngine engine(battleSubject);
    engine.conductBattle(container.getAll(), maxDistance);
}