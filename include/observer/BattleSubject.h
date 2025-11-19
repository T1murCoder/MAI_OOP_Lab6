#pragma once

#include <vector>
#include <memory>

class IBattleObserver;
class NPC;

class BattleSubject {
private:
    std::vector<std::shared_ptr<IBattleObserver>> observers;
    
public:
    void attach(std::shared_ptr<IBattleObserver> observer);
    void detach(std::shared_ptr<IBattleObserver> observer);
    
    void notifyBattleStart(const NPC& attacker, const NPC& defender, float distance);
    void notifyDeath(const NPC& killed, const NPC& killer);
};