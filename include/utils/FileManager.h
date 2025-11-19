#pragma once

#include <vector>
#include <memory>
#include <string>

class NPC;
class NPCFactoryRegistry;

class FileManager {
private:
    NPCFactoryRegistry& registry;
    
public:
    explicit FileManager(NPCFactoryRegistry& registry);
    
    void save(const std::vector<std::unique_ptr<NPC>>& npcs, 
              const std::string& filename);
    
    std::vector<std::unique_ptr<NPC>> load(const std::string& filename);
};