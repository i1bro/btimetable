//
// Created by Ксюша on 16.02.2021.
//

#include "BookingModule.h"
#include <string>

void BookingModule::enterId(dataBase::TestDataBase &testDataBase) {
    id = -1;
    bool isOnlyNumbers = true;
    while (!isOnlyNumbers || !isValidId(id, testDataBase)) {
        std::string input;
        std::cout << "Введите ID события, на которое хотите записаться:\n";
        getline(std::cin, input);
        isOnlyNumbers = true;
        for (auto symbol : input) {
            if (symbol < '0' || symbol > '9') {
                isOnlyNumbers = false;
            }
        }
        if (isOnlyNumbers) {
            id = stoll(input, nullptr, 10);
        }
    }
}

void BookingModule::enterEmail() {
    email = "";
    while (!isValidEmail(email)) {
        std::cout << "Введите свой e-mail в формате example@domain.com:\n";
        getline(std::cin, email);
    }
}

void BookingModule::enterTelephone() {
    telephone = "";
    while (!isValidTelephone(telephone)) {
        std::cout << "Введите свой телефон в формате +7-XXX-XXX-XX-XX:\n";
        getline(std::cin, telephone);
    }
}

bool BookingModule::isValidEmail(std::string &str) {
    int posOfFirstAt = str.find_first_of('@'), posOfLastAt = str.find_last_of('@');
    if (posOfFirstAt != posOfLastAt || posOfFirstAt == std::string::npos) {
        return false;
    }

    int posOfLastDot = str.find_last_of('.');
    if (posOfLastDot == str.size() - 1 || posOfLastDot == std::string::npos) {
        return false;
    }

    if (posOfLastDot == posOfLastAt + 1) {
        return false;
    }
    return true;
}

bool BookingModule::isValidTelephone(std::string &str) {
    if (str.size() != 16) {
        return false;
    }

    if (str[0] != '+' || str[1] != '7') {
        return false;
    }
    int posOfNums[] = {3, 4, 5, 7, 8, 9, 11, 12, 14, 15};
    for (int ind : posOfNums) {
        if (!isdigit(str[ind])) {
            return false;
        }
    }

    int posOfDashes[] = {2, 6, 10, 13};
    for (int ind : posOfDashes) {
        if (str[ind] != '-') {
            return false;
        }
    }

    return true;
}

void BookingModule::run(dataBase::TestDataBase testDataBase) {
    std::cout << "Доступные события:\n";
    for (dataBase::Company comp : testDataBase.companies) {
        std::cout << "Компания " << comp.name << ":\n";
        for (auto &ord : comp.listVacantOrders()) {
            std::cout << "ID события: " << ord->id << ", ID мастера: " << ord->employee_id << ", Время: "
                      << ord->time_start << ", Продолжительность: " << ord->duration << "\n";
        }
    }
    enterId(testDataBase);
    enterEmail();
    enterTelephone();

    std::cout << "ID: " << id << "\ne-mail: " << email << "\nТелефон: " << telephone;
}

bool BookingModule::isValidId(long long &x,
                              dataBase::TestDataBase &testDataBase) {
    bool result = false;
    for (auto comp : testDataBase.companies) {
        if (comp.findOrder(x) != nullptr) {
            result = true;
        }
    }
    return result;
}
