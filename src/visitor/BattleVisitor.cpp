#include "../../include/visitor/BattleVisitor.h"
#include "../../include/npc/Bear.h"
#include "../../include/npc/Werewolf.h"
#include "../../include/npc/Bandit.h"
#include "../../include/observer/BattleSubject.h"

BattleVisitor::BattleVisitor(NPC& opponent, 
                             float maxDistance,
                             std::shared_ptr<BattleSubject> subject,
                             bool& defenderDied)
    : opponent(opponent), maxDistance(maxDistance), subject(subject), defenderDied(defenderDied) {}

bool BattleVisitor::canFight(const NPC& attacker) const {
    if (!attacker.isAlive() || !opponent.isAlive()) {
        return false;
    }

    if (&attacker == &opponent) {
        return false;
    }
    
    if (attacker.distanceTo(opponent) > maxDistance) {
        return false;
    }
    return true;
}

void BattleVisitor::resolveCombat(NPC& attacker, NPC& defender) {
    float distance = attacker.distanceTo(defender);
    
    if (subject) {
        subject->notifyBattleStart(attacker, defender, distance);
    }

    int actualDamage = std::max(0, attacker.getAttackPower());
    defender.takeDamage(actualDamage);

    bool defenderAlive = defender.isAlive();

    if (!defenderAlive) {
        defenderDied = true;
        if (subject) {
            subject->notifyDeath(defender, attacker);
        }
    }
}

void BattleVisitor::visit(Bear& bear) {
    if (!canFight(bear)) {
        return;
    }


    if (opponent.getType() != NPCType::WEREWOLF) {return;}

    resolveCombat(bear, opponent);
}

void BattleVisitor::visit(Werewolf& werewolf) {
    if (!canFight(werewolf)) {
        return;
    }

    if (opponent.getType() != NPCType::BANDIT) {return;}

    resolveCombat(werewolf, opponent);
}

void BattleVisitor::visit(Bandit& bandit) {
    if (!canFight(bandit)) {
        return;
    }

    if (opponent.getType() != NPCType::BEAR) {return;}


    resolveCombat(bandit, opponent);
}