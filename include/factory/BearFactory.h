#pragma once

#include "INPCFactory.h"

class BearFactory : public INPCFactory {
public:
    std::unique_ptr<NPC> createNPC(const std::string& name, const Point& position, const int health, const int damage) override;
    std::unique_ptr<NPC> loadFromFile(std::istream& is) override;
};