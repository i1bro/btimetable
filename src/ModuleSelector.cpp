//
// Created by Ксюша on 09.02.2021.
//

#include "ModuleSelector.h"
#include "AddingEvents.h"

void ModuleSelector::selectModule() {
    std::string input = "0";
    bool isValidInput = false;

    while (!isValidInput) {
        isValidInput = true;
        std::cout << "Введи число от 1 до 3, чтобы выбрать модуль:\n"
                     "1 -- запись;\n"
                     "2 -- составление расписания;\n"
                     "3 -- тестирование структур данных.\n";
        std::cin >> input;

        if (input[0] > '3' || input[0] < '1') {
            isValidInput = false;
        }
        if (input.size() != 1) {
            isValidInput = false;
        }
    }

    char selectedModule = input[0];

    switch (selectedModule) {
        case '1':
            std::cout << "Вы в модуле записи.\n";
            break;
        case '2':
            EventAdder adder;
            adder.addEvent();
            break;
        case '3':
            std::cout << "Вы в модуле тестирования.\n";
            EntryPoint entryPoint;
            entryPoint.run();
            break;
        default:
            std::cout << "Ошибка: неверно введен номер модуля.\n";
            return; // TODO: exception
    }
}
