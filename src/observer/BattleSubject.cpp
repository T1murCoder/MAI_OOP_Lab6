#include "../../include/observer/BattleSubject.h"
#include "../../include/observer/IBattleObserver.h"
#include <algorithm>

void BattleSubject::attach(std::shared_ptr<IBattleObserver> observer) {
    if (observer) {
        observers.push_back(observer);
    }
}

void BattleSubject::detach(std::shared_ptr<IBattleObserver> observer) {
    observers.erase(
        std::remove(observers.begin(), observers.end(), observer),
        observers.end()
    );
}

void BattleSubject::notifyBattleStart(const NPC& attacker, const NPC& defender, float distance) {
    for (auto& observer : observers) {
        if (observer) {
            observer->onBattleStart(attacker, defender, distance);
        }
    }
}


void BattleSubject::notifyDeath(const NPC& killed, const NPC& killer) {
    for (auto& observer : observers) {
        if (observer) {
            observer->onDeath(killed, killer);
        }
    }
}