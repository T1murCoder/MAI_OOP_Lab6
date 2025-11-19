#include "../../include/npc/NPC.h"
#include <cmath>

NPC::NPC(const std::string& name, const Point& position,
         int health, int attackPower)
         : name(name), position(position), health(health), attackPower(attackPower) {}

float NPC::distanceTo(const NPC& other) const {
    return position.distanceTo(other.position);
}

bool NPC::isAlive() const {
    return health > 0;
}

void NPC::takeDamage(int damage) {
    health -= damage;
    if (health < 0) {
        health = 0;
    }
}

const std::string& NPC::getName() const {
    return name;
}

int NPC::getHealth() const {
    return health;
}

int NPC::getAttackPower() const {
    return attackPower;
}

const Point& NPC::getPosition() const {
    return position;
}

std::string NPC::getTypeString() const {
    return npcTypeToString(getType());
}