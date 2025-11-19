#pragma once
#include <string>

enum class NPCType {
    BEAR,
    BANDIT,
    WEREWOLF
};

std::string npcTypeToString(NPCType type);

NPCType stringToNPCType(const std::string& str);