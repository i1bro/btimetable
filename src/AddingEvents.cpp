//
// Created by Petya on 11.02.2021.
//

#include "AddingEvents.h"


void EventAdder::addEvent() {


    while(true){
        std::cout << "1 -- Add an event\n";
        std::cout << "2 -- Exit\n";

        int input;
        std::cin >> input;
        if(input == 2)
            break;
        std::string debug;
        getline(std::cin, debug);//нужно из-за того что в буфере остается пустая строка
        std::cout << "Enter the name of the event" << std::endl;
        std::string event;
        getline(std::cin, event);
        std::cout << "Enter the name of the specialist in the format LastName FirstName\n";
        std::string specialist;
        while(true) {
            std::regex inputPattern(R"(^\s{0,}[a-z,A-Z]{1,20}\s{1,}[a-z,A-Z]{1,20}\s{0,})");
            getline(std::cin, specialist);
            if(std::regex_match(specialist, inputPattern)){
                break;
            }
            std::cout << "Invalid input format, repeat again\n";
        }
        std::cout << "Enter the start date of the event in the format dd.mm.yy\n";
        int day, month, year;
        char c;
        while(true) {
            std::regex inputPattern(R"(^\s{0,}[0-9]{2,2}[.][0-9]{2,2}[.][0-9]{2,2}\s{0,})");
            std::string in;
            getline(std::cin, in);
            if(std::regex_match(in, inputPattern)){
                std::stringstream inputStream1(in);
                inputStream1 >> day >> c >> month >> c >> year;
                if(day >= 0 && day <= 31 && month >= 1 && month <= 12)
                    break;
            }
            std::cout << "Invalid input format, repeat again\n";
        }
        std::cout << "Enter the event start time in the format hr.mt\n";
        int beginHour, beginMinute;
        while(true) {
            std::regex inputPattern(R"(^\s{0,}[0-9]{2,2}[.][0-9]{2,2}\s{0,})");
            std::string in;
            getline(std::cin, in);
            if(std::regex_match(in, inputPattern)){
                std::stringstream inputStream1(in);
                inputStream1 >> beginHour >> c >> beginMinute;
                if(beginHour >= 0 && beginHour <= 23 && beginMinute >= 0 && beginMinute <= 59)
                    break;
            }
            std::cout << "Invalid input format, repeat again\n";
        }
        std::cout << "Enter the end time of the event in the format hr.mt\n";
        int endHour, endMinute;
        while(true) {
            std::regex inputPattern(R"(^\s{0,}[0-9]{2,2}[.][0-9]{2,2}\s{0,})");
            std::string in;
            getline(std::cin, in);
            if(std::regex_match(in, inputPattern)){
                std::stringstream inputStream1(in);
                inputStream1 >> endHour >> c >> endMinute;
                if(endHour >= 0 && endHour <= 23 && endMinute >= 0 && endMinute <= 59)
                    break;
            }
            std::cout << "Invalid input format, repeat again\n";
        }//TODO: вставить в струкруру данных
        std::cout << "Your event: " << event << '\n';
        std::cout << "Specialist: " << specialist << '\n';
        std::cout << "data: " << day << "." << month << '.' << year << '\n';
        std::cout << "time: " << beginHour << '.' << beginMinute << '-' << endHour << '.' << endMinute << '\n';
    }
}