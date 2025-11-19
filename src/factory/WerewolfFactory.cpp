#include <sstream>
#include "../../include/factory/WerewolfFactory.h"
#include "../../include/npc/Werewolf.h"
#include "../../include/utils/Point.h"

std::unique_ptr<NPC> WerewolfFactory::createNPC(const std::string& name, const Point& position, const int health, const int damage) {
    return std::make_unique<Werewolf>(name, position, health, damage);
}

std::unique_ptr<NPC> WerewolfFactory::loadFromFile(std::istream& is) {
    std::string name;
    float x, y;
    int health, damage;
    
    is >> name >> x >> y >> health >> damage;
    
    Point position(x, y);
    return createNPC(name, position, health, damage);
}