#pragma once

class NPC;

class IBattleObserver {
public:
    virtual void onBattleStart(const NPC& attacker, const NPC& defender, float distance) = 0;
    virtual void onDeath(const NPC& killed, const NPC& killer) = 0;
    virtual ~IBattleObserver() = default;
};