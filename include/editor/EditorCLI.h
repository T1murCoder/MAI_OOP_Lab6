#pragma once

#include <string>

class DungeonEditor;

class EditorCLI {
private:
    DungeonEditor& editor;
    
    void printWelcome();
    void printMenu();
    void printSeparator();
    
    void handleAddNPC();
    void handleRemoveNPC();
    void handlePrintNPCs();
    void handleSaveToFile();
    void handleLoadFromFile();
    void handleStartBattle();
    void handleStartBattleRounds();
    
    std::string readString(const std::string& prompt);
    float readFloat(const std::string& prompt);
    int readInt(const std::string& prompt);
    
public:
    explicit EditorCLI(DungeonEditor& editor);
    
    void run();
};