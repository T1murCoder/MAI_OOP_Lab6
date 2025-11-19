#include "../../include/editor/EditorCLI.h"
#include "../../include/editor/DungeonEditor.h"
#include "../../include/visitor/PrintVisitor.h"
#include "../../include/npc/NPC.h"
#include <iostream>
#include <limits>
#include <iomanip>

EditorCLI::EditorCLI(DungeonEditor& editor)
    : editor(editor)
{}

void EditorCLI::printWelcome() {
    printSeparator();
    std::cout << "  Редактор подземелья Balagur Fate 3" << std::endl;
    printSeparator();
    std::cout << std::endl;
}

void EditorCLI::printMenu() {
    std::cout << "\n============ РЕДАКТОР ПОДЗЕМЕЛЬЯ ============" << std::endl;
    std::cout << "1. Добавить NPC" << std::endl;
    std::cout << "2. Удалить NPC" << std::endl;
    std::cout << "3. Показать всех NPC" << std::endl;
    std::cout << "4. Сохранить в файл" << std::endl;
    std::cout << "5. Загрузить из файла" << std::endl;
    std::cout << "6. Запустить боевой режим" << std::endl;
    std::cout << "7. Запустить боевой режим (N раундов)" << std::endl;
    std::cout << "0. Выход" << std::endl;
    std::cout << "=============================================" << std::endl;
    std::cout << "Выберите действие: ";
}

void EditorCLI::printSeparator() {
    std::cout << "=============================================" << std::endl;
}

std::string EditorCLI::readString(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::cin >> value;
    return value;
}

float EditorCLI::readFloat(const std::string& prompt) {
    float value;
    std::cout << prompt;
    
    while (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка: введите число" << std::endl;
        std::cout << prompt;
    }
    
    return value;
}

int EditorCLI::readInt(const std::string& prompt) {
    int value;
    std::cout << prompt;
    
    while (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка: введите целое число" << std::endl;
        std::cout << prompt;
    }
    
    return value;
}

void EditorCLI::handleAddNPC() {
    std::cout << "\n--- Добавление NPC ---" << std::endl;
    std::cout << "Доступные типы: Bear, Werewolf, Bandit" << std::endl;
    
    try {
        std::string type = readString("Введите тип: ");
        std::string name = readString("Введите имя: ");
        float x = readFloat("Введите координату X (0-500): ");
        float y = readFloat("Введите координату Y (0-500): ");
        int health = readInt("Введите здоровье: ");
        int damage = readInt("Введите силу атаки: ");
        
        editor.addNPC(type, name, x, y, health, damage);
        std::cout << "Успех! NPC \"" << name << "\" добавлен." << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void EditorCLI::handleRemoveNPC() {
    std::cout << "\n--- Удаление NPC ---" << std::endl;
    
    if (editor.getContainer().size() == 0) {
        std::cout << "В подземелье нет NPC." << std::endl;
        return;
    }
    
    try {
        std::string name = readString("Введите имя NPC для удаления: ");
        editor.removeNPC(name);
        std::cout << "Успех! NPC \"" << name << "\" удален." << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void EditorCLI::handlePrintNPCs() {
    const auto& container = editor.getContainer();
    
    if (container.size() == 0) {
        std::cout << "\nВ подземелье нет NPC." << std::endl;
        return;
    }
    
    std::cout << "\n========== СПИСОК NPC В ПОДЗЕМЕЛЬЕ ==========" << std::endl;
    std::cout << "Всего NPC: " << container.size() << std::endl;
    printSeparator();
    
    PrintVisitor printer;
    for (const auto& npc : container.getAll()) {
        if (npc) {
            npc->accept(printer);
        }
    }
    
    printSeparator();
}

void EditorCLI::handleSaveToFile() {
    std::cout << "\n--- Сохранение в файл ---" << std::endl;
    
    if (editor.getContainer().size() == 0) {
        std::cout << "Нечего сохранять - подземелье пусто." << std::endl;
        return;
    }
    
    try {
        std::string filename = readString("Введите имя файла: ");
        editor.saveToFile(filename);
        std::cout << "Успех! Данные сохранены в файл \"" << filename << "\"" << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void EditorCLI::handleLoadFromFile() {
    std::cout << "\n--- Загрузка из файла ---" << std::endl;
    
    try {
        std::string filename = readString("Введите имя файла: ");
        size_t beforeCount = editor.getContainer().size();
        
        editor.loadFromFile(filename);
        
        size_t afterCount = editor.getContainer().size();
        size_t loaded = afterCount - beforeCount;
        
        std::cout << "Успех! Загружено NPC: " << loaded << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void EditorCLI::handleStartBattle() {
    std::cout << "\n--- Боевой режим ---" << std::endl;
    
    if (editor.getContainer().size() == 0) {
        std::cout << "В подземелье нет NPC для боя." << std::endl;
        return;
    }
    
    try {
        float maxDistance = readFloat("Введите максимальную дистанцию боя: ");
        
        size_t beforeCount = editor.getContainer().size();
        
        std::cout << "\n========== НАЧАЛО БОЕВОГО РЕЖИМА ==========" << std::endl;
        std::cout << "Максимальная дистанция боя: " << maxDistance << " м" << std::endl;
        std::cout << "Участников: " << beforeCount << std::endl;
        std::cout << "Режим: бой до конца (пока есть разные типы)" << std::endl;
        printSeparator();
        std::cout << std::endl;
        
        editor.startBattle(maxDistance);
        
        size_t afterCount = editor.getContainer().size();
        
        std::cout << "\n========== КОНЕЦ БОЕВОГО РЕЖИМА ==========" << std::endl;
        std::cout << "Выживших: " << afterCount << std::endl;
        std::cout << "Погибло: " << (beforeCount - afterCount) << std::endl;
        printSeparator();
        
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void EditorCLI::handleStartBattleRounds() {
    std::cout << "\n--- Боевой режим (раунды) ---" << std::endl;
    
    if (editor.getContainer().size() == 0) {
        std::cout << "В подземелье нет NPC для боя." << std::endl;
        return;
    }
    
    try {
        float maxDistance = readFloat("Введите максимальную дистанцию боя: ");
        
        if (maxDistance <= 0) {
            std::cout << "Дистанция должна быть положительной." << std::endl;
            return;
        }
        
        int rounds = readInt("Введите количество раундов: ");
        
        if (rounds <= 0) {
            std::cout << "Количество раундов должно быть положительным." << std::endl;
            return;
        }
        
        size_t beforeCount = editor.getContainer().size();
        
        std::cout << "\n========== НАЧАЛО БОЕВОГО РЕЖИМА ==========" << std::endl;
        std::cout << "Максимальная дистанция боя: " << maxDistance << " м" << std::endl;
        std::cout << "Участников: " << beforeCount << std::endl;
        std::cout << "Режим: " << rounds << " раунд(ов)" << std::endl;
        printSeparator();
        std::cout << std::endl;
        
        int completedRounds = editor.startBattleRounds(maxDistance, rounds);
        
        size_t afterCount = editor.getContainer().size();
        
        std::cout << "\n========== КОНЕЦ БОЕВОГО РЕЖИМА ==========" << std::endl;
        std::cout << "Проведено раундов: " << completedRounds << " из " << rounds << std::endl;
        std::cout << "Выживших: " << afterCount << std::endl;
        std::cout << "Погибло: " << (beforeCount - afterCount) << std::endl;
        
        if (completedRounds < rounds) {
            std::cout << "Битва завершена досрочно (остались NPC одного типа)" << std::endl;
        }
        
        printSeparator();
        
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void EditorCLI::run() {
    printWelcome();
    
    bool running = true;
    while (running) {
        printMenu();
        
        int choice = readInt("");
        
        std::cout << std::endl;
        
        switch (choice) {
            case 1:
                handleAddNPC();
                break;
            case 2:
                handleRemoveNPC();
                break;
            case 3:
                handlePrintNPCs();
                break;
            case 4:
                handleSaveToFile();
                break;
            case 5:
                handleLoadFromFile();
                break;
            case 6:
                handleStartBattle();
                break;
            case 7:
                handleStartBattleRounds();
                break;
            case 0:
                std::cout << "Выход из программы..." << std::endl;
                running = false;
                break;
            default:
                std::cout << "Ошибка: неверный выбор. Введите число от 0 до 6" << std::endl;
                break;
        }
    }
}