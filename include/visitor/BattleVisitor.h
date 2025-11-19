#pragma once

#include "INPCVisitor.h"
#include <memory>

class NPC;
class BattleSubject;

class BattleVisitor : public INPCVisitor {
private:
    NPC& opponent;
    float maxDistance;
    std::shared_ptr<BattleSubject> subject;
    bool& defenderDied;

    bool canFight(const NPC& attacker) const;
    void resolveCombat(NPC& attacker, NPC& defender);
public:
    BattleVisitor(NPC& opponent, float maxDistance, std::shared_ptr<BattleSubject> subject, bool& defenderDied);

    void visit(Bear& bear) override;
    void visit(Werewolf& werewolf) override;
    void visit(Bandit& bandit) override;
};