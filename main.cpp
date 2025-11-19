#include "include/editor/DungeonEditor.h"
#include "include/editor/EditorCLI.h"

#include "include/npc/NPC.h"
#include "include/npc/Bear.h"
#include "include/npc/Werewolf.h"
#include "include/npc/Bandit.h"
#include "include/factory/INPCFactory.h"
#include "include/factory/BearFactory.h"
#include "include/factory/WerewolfFactory.h"
#include "include/factory/BanditFactory.h"

#include <iostream>
#include <exception>

int main() {
    try {
        DungeonEditor editor;
        
        EditorCLI cli(editor);
        
        cli.run();   
    } catch (const std::exception& e) {
        std::cerr << "Критическая ошибка: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Неизвестная критическая ошибка" << std::endl;
        return 2;
    }
    
    return 0;
}