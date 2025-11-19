#pragma once

#include "IBattleObserver.h"

class ConsoleObserver : public IBattleObserver {
public:
    void onBattleStart(const NPC& attacker, const NPC& defender, float distance) override;
    void onDeath(const NPC& killed, const NPC& killer) override;
};