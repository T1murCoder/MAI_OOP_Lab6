#pragma once

#include <vector>
#include <memory>
#include <string>

class NPC;

class NPCContainer {
private:
    std::vector<std::unique_ptr<NPC>> npcs;

public:
    void add(std::unique_ptr<NPC> npc);
    void remove(const std::string& name);
    
    std::vector<std::unique_ptr<NPC>>& getAll();
    const std::vector<std::unique_ptr<NPC>>& getAll() const;
    
    bool hasName(const std::string& name) const;
    size_t size() const;
    void clear();
};