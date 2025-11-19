#include "../../include/npc/Bandit.h"
#include "../../include/visitor/INPCVisitor.h"

Bandit::Bandit(const std::string& name, const Point& position, int health, int attackPower)
    : NPC(name, position, health, attackPower) {}

void Bandit::accept(INPCVisitor& visitor) {
    visitor.visit(*this);
}

NPCType Bandit::getType() const {
    return NPCType::BANDIT;
}