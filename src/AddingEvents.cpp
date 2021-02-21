//
// Created by Petya on 11.02.2021.
//

#include "AddingEvents.h"


void EventAdder::addEvent() {


    while(true){
        std::cout << "1 -- Add an event\n";
        std::cout << "2 -- Exit\n";
        int inputInt = 0;
        while(true) {
            std::regex inputPattern(R"(^\s{0,}[1-2]{1,1}\s{0,})");
            std::string input;
            getline(std::cin, input);
            if(std::regex_match(input, inputPattern)){
                std::stringstream inputStream1(input);
                inputStream1 >> inputInt;
                break;
            }
            std::cout << "Invalid input format, repeat again\n";
        }
        if(inputInt == 2)
            break;
        std::string event;
        std::cout << "Enter the name of the event" << std::endl;
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
        std::cout << "enter the number of minutes that the event will last\n";
        int duration = 0;
        while(true) {
            std::regex inputPattern(R"(^\s{0,}[0-9]{1,}\s{0,})");
            std::string in;
            getline(std::cin, in);
            if(std::regex_match(in, inputPattern)){
                std::stringstream inputStream1(in);
                inputStream1 >> duration;
                break;
            }
            std::cout << "Invalid input format, repeat again\n";
        }//TODO: вставить в струкруру данных
        std::cout << "Your event: " << event << '\n';
        std::cout << "Specialist: " << specialist << '\n';
        std::cout << "date: " << day << "." << month << '.' << year << '\n';
        std::cout << "starttime: " << beginHour << '.' << beginMinute << '\n';
        std::cout << "duration: " << duration << " minutes\n";
    }
}