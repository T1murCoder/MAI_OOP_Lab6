#pragma once

#include "INPCVisitor.h"
#include <memory>

class NPC;
class BattleSubject;

class PrintVisitor : public INPCVisitor {
public:    
    void visit(Bear& bear) override;
    void visit(Werewolf& werewolf) override;
    void visit(Bandit& bandit) override;
};