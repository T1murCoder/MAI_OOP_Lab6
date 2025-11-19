#pragma once

#include "NPC.h"

class Werewolf : public NPC {
public:
    Werewolf(const std::string& name, const Point& position, int health, int attackPower);

    void accept(INPCVisitor& visitor) override;
    NPCType getType() const override;
};