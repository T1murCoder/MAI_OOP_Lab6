#include "../../include/observer/FileObserver.h"
#include "../../include/npc/NPC.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <sstream>

FileObserver::FileObserver(const std::string& filename)
    : filename(filename)
{
    logFile.open(filename, std::ios::out | std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл лога " << filename << std::endl;
    } else {
        writeLog("=== Начало новой сессии боев ===");
    }
}

FileObserver::~FileObserver() {
    if (logFile.is_open()) {
        writeLog("=== Конец сессии боев ===");
        writeLog("");
        logFile.close();
    }
}

std::string FileObserver::getCurrentTimestamp() const {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

void FileObserver::writeLog(const std::string& message) {
    if (logFile.is_open()) {
        logFile << "[" << getCurrentTimestamp() << "] " << message << std::endl;
        logFile.flush();
    }
}

void FileObserver::onBattleStart(const NPC& attacker, const NPC& defender, float distance) {
    std::stringstream ss;
    ss << "БОЙ НАЧАЛСЯ: [" << attacker.getTypeString() << "] \"" << attacker.getName() 
       << "\" атакует [" << defender.getTypeString() << "] \"" << defender.getName() 
       << "\" на дистанции " << std::fixed << std::setprecision(2) << distance << " м";
    writeLog(ss.str());
}

void FileObserver::onDeath(const NPC& killed, const NPC& killer) {
    std::stringstream ss;
    ss << "УБИЙСТВО: [" << killer.getTypeString() << "] \"" << killer.getName() 
       << "\" убил [" << killed.getTypeString() << "] \"" << killed.getName() << "\"";
    writeLog(ss.str());
}