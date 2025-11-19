#include "../../include/observer/ConsoleObserver.h"
#include "../../include/npc/NPC.h"
#include <iostream>
#include <iomanip>

void ConsoleObserver::onBattleStart(const NPC& attacker, const NPC& defender, float distance) {
    std::cout << "БОЙ НАЧАЛСЯ!" << std::endl;
    std::cout << "  Атакующий: [" << attacker.getTypeString()  << "]"
              << " \"" << attacker.getName() << "\"" << std::endl;
    std::cout << "  Защищающийся: [" << defender.getTypeString() << "]"
              << " \"" << defender.getName() << "\"" << std::endl;
    std::cout << "  Дистанция: " << std::fixed << std::setprecision(2) 
              << distance << " м" << std::endl;
    std::cout << std::endl;
}

void ConsoleObserver::onDeath(const NPC& killed, const NPC& killer) {
    std::cout << "УБИЙСТВО!" << std::endl;
    std::cout << "  [" << killer.getTypeString() << "] \"" << killer.getName() 
              << "\" убил [" << killed.getTypeString() << "] \"" << killed.getName() 
              << "\"" << std::endl;
    std::cout << std::endl;
}