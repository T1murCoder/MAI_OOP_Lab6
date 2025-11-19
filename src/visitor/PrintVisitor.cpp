#include "../../include/visitor/PrintVisitor.h"
#include "../../include/npc/Bear.h"
#include "../../include/npc/Werewolf.h"
#include "../../include/npc/Bandit.h"
#include <iostream>
#include <iomanip>

void PrintVisitor::visit(Bear& bear) {
    std::cout << "[Медведь] " 
              << std::setw(15) << std::left << bear.getName()
              << " | Позиция: (" 
              << std::fixed << std::setprecision(2)
              << std::setw(6) << bear.getPosition().getX() << ", "
              << std::setw(6) << bear.getPosition().getY() << ")"
              << " | HP: " << std::setw(3) << bear.getHealth()
              << " | Атака: " << std::setw(2) << bear.getAttackPower()
              << std::endl;
}

void PrintVisitor::visit(Werewolf& werewolf) {
    std::cout << "[Оборотень] " 
              << std::setw(15) << std::left << werewolf.getName()
              << " | Позиция: (" 
              << std::fixed << std::setprecision(2)
              << std::setw(6) << werewolf.getPosition().getX() << ", "
              << std::setw(6) << werewolf.getPosition().getY() << ")"
              << " | HP: " << std::setw(3) << werewolf.getHealth()
              << " | Атака: " << std::setw(2) << werewolf.getAttackPower()
              << std::endl;
}

void PrintVisitor::visit(Bandit& bandit) {
    std::cout << "[Разбойник] " 
              << std::setw(15) << std::left << bandit.getName()
              << " | Позиция: (" 
              << std::fixed << std::setprecision(2)
              << std::setw(6) << bandit.getPosition().getX() << ", "
              << std::setw(6) << bandit.getPosition().getY() << ")"
              << " | HP: " << std::setw(3) << bandit.getHealth()
              << " | Атака: " << std::setw(2) << bandit.getAttackPower()
              << std::endl;
}