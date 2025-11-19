#pragma once

#include "NPC.h"

class Bandit : public NPC {
public:
    Bandit(const std::string& name, const Point& position, int health, int attackPower);

    void accept(INPCVisitor& visitor) override;
    NPCType getType() const override;
};