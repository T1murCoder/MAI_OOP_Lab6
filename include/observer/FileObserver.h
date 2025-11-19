#pragma once

#include "IBattleObserver.h"
#include <string>
#include <fstream>

class FileObserver : public IBattleObserver {
private:
    std::string filename;
    std::ofstream logFile;
    
    std::string getCurrentTimestamp() const;
    void writeLog(const std::string& message);
    
public:
    explicit FileObserver(const std::string& filename);
    
    void onBattleStart(const NPC& attacker, const NPC& defender, float distance) override;
    void onDeath(const NPC& killed, const NPC& killer) override;

    ~FileObserver();
};