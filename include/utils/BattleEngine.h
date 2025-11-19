#pragma once

#include <vector>
#include <memory>

class NPC;
class BattleSubject;

class BattleEngine {
private:
    std::shared_ptr<BattleSubject> subject;
    
    void fight(NPC& attacker, NPC& defender, float maxDistance, bool& defenderDied);
    
    void removeDeadNPCs(std::vector<std::unique_ptr<NPC>>& npcs);

    bool hasDifferentTypes(const std::vector<std::unique_ptr<NPC>>& npcs) const;
    
public:
    explicit BattleEngine(std::shared_ptr<BattleSubject> subject);
    
    bool conductRound(std::vector<std::unique_ptr<NPC>>& npcs, float maxDistance);
    
    int conductRounds(std::vector<std::unique_ptr<NPC>>& npcs, float maxDistance, int maxRounds);
    
    void conductBattle(std::vector<std::unique_ptr<NPC>>& npcs, float maxDistance);
};