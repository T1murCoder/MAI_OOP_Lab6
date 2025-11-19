#include "../../include/npc/Werewolf.h"
#include "../../include/visitor/INPCVisitor.h"

Werewolf::Werewolf(const std::string& name, const Point& position, int health, int attackPower)
    : NPC(name, position, health, attackPower) {}

void Werewolf::accept(INPCVisitor& visitor) {
    visitor.visit(*this);
}

NPCType Werewolf::getType() const {
    return NPCType::WEREWOLF;
}