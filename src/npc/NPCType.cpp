#include "../../include/npc/NPCType.h"

#include <stdexcept>

std::string npcTypeToString(NPCType type) {
    switch (type) {
    case NPCType::BEAR: return "Bear";
    case NPCType::BANDIT: return "Bandit";
    case NPCType::WEREWOLF: return "Werewolf";
    default: return "Unknown";
    }
}

NPCType stringToNPCType(const std::string& str) {
    if (str == "Bear") return NPCType::BEAR;
    if (str == "Bandit") return NPCType::BANDIT;
    if (str == "Werewolf") return NPCType::WEREWOLF;
    throw std::invalid_argument("Unknown NPC type: " + str);
}