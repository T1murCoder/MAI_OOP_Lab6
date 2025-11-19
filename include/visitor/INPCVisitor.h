#pragma once

class Bear;
class Werewolf;
class Bandit;

class INPCVisitor {
public:
    virtual void visit(Bear& bear) = 0;
    virtual void visit(Werewolf& werewolf) = 0;
    virtual void visit(Bandit& bandit) = 0;
    virtual ~INPCVisitor() = default;
};