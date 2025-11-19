#include "../../include/utils/FileManager.h"
#include "../../include/factory/NPCFactoryRegistry.h"
#include "../../include/npc/NPC.h"
#include <fstream>
#include <stdexcept>
#include <sstream>

FileManager::FileManager(NPCFactoryRegistry& registry)
    : registry(registry)
{}

void FileManager::save(const std::vector<std::unique_ptr<NPC>>& npcs, 
                       const std::string& filename) {
    std::ofstream file(filename);
    
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл для записи: " + filename);
    }
    
    for (const auto& npc : npcs) {
        if (npc) {
            file << npc->getTypeString() << " "
                 << npc->getName() << " "
                 << npc->getPosition().getX() << " "
                 << npc->getPosition().getY() << " "
                 << npc->getHealth() << " "
                 << npc->getAttackPower() << "\n";
        }
    }
    
    file.close();
    
    if (file.fail()) {
        throw std::runtime_error("Ошибка при записи в файл: " + filename);
    }
}

std::vector<std::unique_ptr<NPC>> FileManager::load(const std::string& filename) {
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл для чтения: " + filename);
    }
    
    std::vector<std::unique_ptr<NPC>> npcs;
    std::string line;
    int lineNumber = 0;
    
    while (std::getline(file, line)) {
        lineNumber++;
        
        if (line.empty() || line.find_first_not_of(" \t\n\r") == std::string::npos) {
            continue;
        }
        
        std::istringstream iss(line);
        
        try {
            auto npc = registry.loadNPC(iss);
            npcs.push_back(std::move(npc));
            
        } catch (const std::exception& e) {
            throw std::runtime_error(
                "Ошибка в строке " + std::to_string(lineNumber) + 
                " файла " + filename + ": " + e.what()
            );
        }
    }
    
    file.close();
    
    return npcs;
}