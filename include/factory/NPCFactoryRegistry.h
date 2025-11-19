#pragma once

#include <map>
#include <string>
#include <memory>
#include "../npc/NPCType.h"

class INPCFactory;
class NPC;
class Point;

class NPCFactoryRegistry {
private:
    std::map<NPCType, std::unique_ptr<INPCFactory>> factories;

public:
    void registerFactory(NPCType, std::unique_ptr<INPCFactory> factory);

    std::unique_ptr<NPC> createNPC(NPCType type, const std::string& name, const Point& position, const int health, const int damage);
    
    std::unique_ptr<NPC> createNPC(const std::string& typeStr, const std::string& name, const Point& position, const int health, const int damage);
    
    std::unique_ptr<NPC> loadNPC(std::istream& is);
};