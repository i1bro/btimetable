//
// Created by Ilya on 10.02.2021.
//

#include "iostream"
#include "EntryPoint.h"
#include "Entities.h"

void EntryPoint::run() {
    dataBase::Company test("test");
    std::cout << "> ";
    while(!std::cin.eof()) {
        std::string command;
        std::cin >> command;
        if(command == "list_emp") {
            test.stdPrintEmployees();
        }
        if(command == "list_cli") {
            test.stdPrintClients();
        }
        if(command == "list_ord") {
            test.schedule.stdPrint();
        }
        if(command == "add_emp") {
            int id;
            std::string name;
            std::cin >> id >> name;
            test.addEmployee(id, std::move(name));
        }
        if(command == "add_cli") {
            int id;
            std::string name;
            std::cin >> id >> name;
            test.addClient(id, std::move(name));
        }
        std::cout << "> ";
    }
}