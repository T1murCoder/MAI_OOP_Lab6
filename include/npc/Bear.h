#pragma once

#include "NPC.h"

class Bear : public NPC {
public:
    Bear(const std::string& name, const Point& position, int health, int attackPower);

    void accept(INPCVisitor& visitor) override;
    NPCType getType() const override;
};