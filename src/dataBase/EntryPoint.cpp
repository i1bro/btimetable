//
// Created by Ilya on 10.02.2021.
//

#include "iostream"
#include "EntryPoint.h"
#include "Entities.h"

void EntryPoint::run() {
    dataBase::Company test("test");
    std::cout << "> ";
    while (!std::cin.eof()) {
        std::string command;
        std::cin >> command;
        if (command == "list_emp") {
            for (auto &i: test.listEmployees()) {
                i -> stdPrint();
                std::cout << "\n";
            }
        }
        if (command == "list_cli") {
            for (auto &i: test.listClients()) {
                i -> stdPrint();
                std::cout << "\n";
            }
        }
        if (command == "list_ord") {
            for (auto &i: test.listOrders()) {
                i -> stdPrint();
                std::cout << "\n";
            }
        }
        if (command == "add_emp") {
            int id;
            std::string name;
            std::cin >> id >> name;
            test.addEmployee(id, std::move(name));
        }
        if (command == "add_cli") {
            int id;
            std::string name;
            std::cin >> id >> name;
            test.addClient(id, std::move(name));
        }
        if (command == "add_ord") {
            int id, time_start, duration, client_id, employee_id;
            std::cin >> id >> time_start >> duration >> client_id >> employee_id;
            test.addOrder(id, time_start, duration, client_id, employee_id);
        }
        if (command == "del_emp") {
            int id;
            std::cin >> id;
            test.deleteEmployee(id);
        }
        if (command == "del_cli") {
            int id;
            std::cin >> id;
            test.deleteClient(id);
        }
        if (command == "del_ord") {
            int id;
            std::cin >> id;
            test.deleteOrder(id);
        }
        if (command == "find_emp") {
            int id;
            std::cin >> id;
            test.findEmployee(id)->stdPrint();
        }
        if (command == "find_cli") {
            int id;
            std::cin >> id;
            test.findClient(id)->stdPrint();
        }
        if (command == "find_ord") {
            int id;
            std::cin >> id;
            test.findOrder(id)->stdPrint();
        }
        if (command == "exit") {
            return;
        }
        std::cout << "> ";
    }
}