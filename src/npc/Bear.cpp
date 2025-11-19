#include "../../include/npc/Bear.h"
#include "../../include/visitor/INPCVisitor.h"

Bear::Bear(const std::string& name, const Point& position, int health, int attackPower)
    : NPC(name, position, health, attackPower) {}

void Bear::accept(INPCVisitor& visitor) {
    visitor.visit(*this);
}

NPCType Bear::getType() const {
    return NPCType::BEAR;
}