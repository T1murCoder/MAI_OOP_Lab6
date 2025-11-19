#include <sstream>
#include <stdexcept>
#include "../../include/factory/NPCFactoryRegistry.h"
#include "../../include/factory/INPCFactory.h"
#include "../../include/npc/NPC.h"
#include "../../include/utils/Point.h"

void NPCFactoryRegistry::registerFactory(NPCType type, std::unique_ptr<INPCFactory> factory) {
    if (!factory) {
        throw std::invalid_argument("Невозможно зарегистрировать null factory");
    }
    factories[type] = std::move(factory);
}

std::unique_ptr<NPC> NPCFactoryRegistry::createNPC(
    NPCType type, 
    const std::string& name,
    const Point& position,
    const int health,
    const int damage
) {
    auto it = factories.find(type);
    if (it == factories.end()) {
        throw std::invalid_argument("Factory не зарегистрирована для типа: " + 
                                   npcTypeToString(type));
    }
    return it->second->createNPC(name, position, health, damage);
}

std::unique_ptr<NPC> NPCFactoryRegistry::createNPC(
    const std::string& typeStr,
    const std::string& name,
    const Point& position,
    const int health,
    const int damage
) {
    NPCType type = stringToNPCType(typeStr);
    return createNPC(type, name, position, health, damage);
}

std::unique_ptr<NPC> NPCFactoryRegistry::loadNPC(std::istream& is) {
    std::string typeStr;
    is >> typeStr;
    
    if (typeStr.empty()) {
        throw std::runtime_error("Ошибка чтения данных NPC из потока");
    }
    
    NPCType type = stringToNPCType(typeStr);
    
    auto it = factories.find(type);
    if (it == factories.end()) {
        throw std::invalid_argument("Factory не зарегистрирована для типа: " + typeStr);
    }
    
    return it->second->loadFromFile(is);
}