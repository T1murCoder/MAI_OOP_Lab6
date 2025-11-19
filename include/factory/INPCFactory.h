#pragma once
#include <memory>
#include <string>

class NPC;
class Point;

class INPCFactory {
public:
    virtual std::unique_ptr<NPC> createNPC(const std::string& name, const Point& position, int health, int damage) = 0;
    virtual std::unique_ptr<NPC> loadFromFile(std::istream& is) = 0;
    virtual ~INPCFactory() = default;
};