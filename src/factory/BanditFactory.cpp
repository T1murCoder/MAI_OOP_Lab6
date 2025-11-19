#include <sstream>
#include "../../include/factory/BanditFactory.h"
#include "../../include/npc/Bandit.h"
#include "../../include/utils/Point.h"

std::unique_ptr<NPC> BanditFactory::createNPC(const std::string& name, const Point& position, const int health, const int damage) {
    return std::make_unique<Bandit>(name, position, health, damage);
}

std::unique_ptr<NPC> BanditFactory::loadFromFile(std::istream& is) {
    std::string name;
    float x, y;
    int health, damage;
    
    is >> name >> x >> y >> health >> damage;
    
    Point position(x, y);
    return createNPC(name, position, health, damage);
}