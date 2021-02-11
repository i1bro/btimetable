//
// Created by Petya on 11.02.2021.
//

#include "AddingEvents.h"

void EventAdder::addEvent() {


    while(1){
        std::cout << "1 -- Добавить событие\n";
        std::cout << "2 -- Выход\n";

        int input;
        std::cin >> input;
        if(input == 2)
            break;

        std::cout << "Введите название услуги\n";
        std::string event;
        getline(std::cin, event);//TODO: вставить в струкруру данных, валидацию данных

        std::cout << "Введите имя специалиста\n";
        std::string specialist;
        getline(std::cin, specialist);//TODO: вставить в струкруру данных

        std::cout << "Введите дату начала услуги в формате dd.mm.yy\n";
        int day, month, year;
        char c;
        std::cin >> day >> c >> month >> c >> year;//TODO: вставить в струкруру данных, валидацию данных

        std::cout << "Введите время начала услуги в формате hr.mt\n";
        int beginHour, beginMinute;
        std::cin >> beginHour >> c >> beginMinute;//TODO: вставить в струкруру данных, валидацию данных

        std::cout << "Введите время окончания услуги в формате hr.mt\n";
        int endHour, endMinute;
        std::cin >> endHour >> c >> endMinute;//TODO: вставить в струкруру данных, валидацию данных

//        std::cout << "Ваша услуга"
    }

}