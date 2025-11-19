#include "../../include/utils/BattleEngine.h"
#include "../../include/npc/NPC.h"
#include "../../include/observer/BattleSubject.h"
#include "../../include/visitor/BattleVisitor.h"
#include <algorithm>
#include <stdexcept>
#include <set>

BattleEngine::BattleEngine(std::shared_ptr<BattleSubject> subject)
    : subject(subject)
{
    if (!subject) {
        throw std::invalid_argument("BattleSubject cannot be null");
    }
}

void BattleEngine::fight(NPC& attacker, NPC& defender, float maxDistance, bool& defenderDied) {

    BattleVisitor visitor(defender, maxDistance, subject, defenderDied);
    
    attacker.accept(visitor);
}

void BattleEngine::removeDeadNPCs(std::vector<std::unique_ptr<NPC>>& npcs) {
    npcs.erase(
        std::remove_if(npcs.begin(), npcs.end(),
            [](const std::unique_ptr<NPC>& npc) {
                return !npc || !npc->isAlive();
            }),
        npcs.end()
    );
}

bool BattleEngine::hasDifferentTypes(const std::vector<std::unique_ptr<NPC>>& npcs) const {
    if (npcs.size() < 2) {
        return false;
    }
    
    std::set<NPCType> types;
    for (const auto& npc : npcs) {
        if (npc && npc->isAlive()) {
            types.insert(npc->getType());
        }
    }
    
    return types.size() > 1;
}

bool BattleEngine::conductRound(std::vector<std::unique_ptr<NPC>>& npcs, float maxDistance) {
    if (maxDistance <= 0) {
        throw std::invalid_argument("Максимальное расстояние должно быть положительным");
    }
    
    if (npcs.size() < 2) {
        return false;
    }
    
    bool anyDeath = false;
    
    for (size_t i = 0; i < npcs.size(); ++i) {
        if (!npcs[i] || !npcs[i]->isAlive()) {
            continue;
        }
        
        for (size_t j = 0; j < npcs.size(); ++j) {
            if (i == j) {
                continue;
            }
            
            if (!npcs[j] || !npcs[j]->isAlive()) {
                continue;
            }
            
            bool defenderDied = false;
            
            fight(*npcs[i], *npcs[j], maxDistance, defenderDied);
            
            if (defenderDied) {
                anyDeath = true;
            }
        }
    }
    
    removeDeadNPCs(npcs);
    
    return anyDeath;
}

int BattleEngine::conductRounds(std::vector<std::unique_ptr<NPC>>& npcs, float maxDistance, int maxRounds) {
    if (maxRounds <= 0) {
        throw std::invalid_argument("Количество раундов должно быть положительным");
    }
    
    int roundsCompleted = 0;
    
    for (int i = 0; i < maxRounds; ++i) {
        if (!hasDifferentTypes(npcs)) {
            break;
        }
        
        conductRound(npcs, maxDistance);
        roundsCompleted++;
    }
    
    return roundsCompleted;
}

void BattleEngine::conductBattle(std::vector<std::unique_ptr<NPC>>& npcs, 
                                 float maxDistance) {
    if (maxDistance <= 0) {
        throw std::invalid_argument("Максимальное расстояние должно быть положительным");
    }
    
    while (hasDifferentTypes(npcs)) {
        for (size_t i = 0; i < npcs.size(); ++i) {
            if (!npcs[i] || !npcs[i]->isAlive()) {
                continue;
            }
            
            for (size_t j = 0; j < npcs.size(); ++j) {
                if (i == j) {
                    continue;
                }
                
                if (!npcs[j] || !npcs[j]->isAlive()) {
                    continue;
                }
                
                bool defenderDied = false;
                
                fight(*npcs[i], *npcs[j], maxDistance, defenderDied);
            }
        }
        
        removeDeadNPCs(npcs);
    }
}