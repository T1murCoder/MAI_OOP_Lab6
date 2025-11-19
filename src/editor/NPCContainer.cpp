#include "../../include/editor/NPCContainer.h"
#include "../../include/npc/NPC.h"
#include <algorithm>
#include <stdexcept>

void NPCContainer::add(std::unique_ptr<NPC> npc) {
    if (!npc) {
        throw std::invalid_argument("NPC не может быть null");
    }
    
    if (hasName(npc->getName())) {
        throw std::invalid_argument("NPC с именем \"" + npc->getName() + "\" уже существует");
    }
    
    npcs.push_back(std::move(npc));
}

void NPCContainer::remove(const std::string& name) {
    npcs.erase(
        std::remove_if(npcs.begin(), npcs.end(),
            [&name](const std::unique_ptr<NPC>& npc) {
                return npc && npc->getName() == name;
            }),
        npcs.end()
    );
}

std::vector<std::unique_ptr<NPC>>& NPCContainer::getAll() {
    return npcs;
}

const std::vector<std::unique_ptr<NPC>>& NPCContainer::getAll() const {
    return npcs;
}

bool NPCContainer::hasName(const std::string& name) const {
    return std::any_of(npcs.begin(), npcs.end(),
        [&name](const std::unique_ptr<NPC>& npc) {
            return npc && npc->getName() == name;
        });
}

size_t NPCContainer::size() const {
    return npcs.size();
}

void NPCContainer::clear() {
    npcs.clear();
}