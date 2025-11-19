#pragma once
#include <string>
#include "NPCType.h"
#include "../utils/Point.h"

class INPCVisitor;

class NPC {
protected:
    std::string name;
    Point position;
    int health;
    int attackPower;

public:
    NPC(const std::string& name, const Point& position, int health, int attackPower);

    virtual ~NPC() = default;

    virtual void accept(INPCVisitor& visitor) = 0;
    
    virtual NPCType getType() const = 0;

    float distanceTo(const NPC& other) const;
    bool isAlive() const;
    void takeDamage(const int dmg);

    const std::string& getName() const;
    int getHealth() const;
    int getAttackPower() const;
    const Point& getPosition() const;
    std::string getTypeString() const;
};