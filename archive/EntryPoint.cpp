#include "EntryPoint.h"
#include "Entities.h"
#include "btt/Storage.h"
#include "iostream"

void EntryPoint::run() {
    /*
    dataBase::Company test("test");
    dataBase::Storage st;
    std::cout << "> ";
    while (!std::cin.eof()) {
        std::string command;
        std::cin >> command;
        if (command == "list_emp") {
            for (auto &i : test.listEmployees()) {
                i->stdPrint();
                std::cout << "\n";
            }
        }
        if (command == "list_cli") {
            for (auto &i : test.listClients()) {
                i->stdPrint();
                std::cout << "\n";
            }
        }
        if (command == "list_ord") {
            std::cout << "Vacant:\n";
            for (auto &i : test.listVacantOrders()) {
                std::cout << "  ";
                i->stdPrint();
                std::cout << "\n";
            }
            std::cout << "Booked:\n";
            for (auto &i : test.listBookedOrders()) {
                std::cout << "  ";
                i->stdPrint();
                std::cout << "\n";
            }
        }
        if (command == "add_emp") {
            std::string name;
            std::cin >> name;
            test.addEmployee(std::move(name));
        }
        if (command == "add_cli") {
            std::string name;
            std::cin >> name;
            test.addClient(std::move(name));
        }
        if (command == "add_ord") {
            std::string title;
            int time_start, duration, employee_id;
            std::cin >> title >> time_start >> duration >> employee_id;
            test.addOrder(std::move(title), time_start, duration, employee_id);
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
            auto res = test.findEmployee(id);
            if (res) {
                res->stdPrint();
            } else {
                std::cout << "Incorrect id";
            }
            std::cout << "\n";
        }
        if (command == "find_cli") {
            int id;
            std::cin >> id;
            auto res = test.findClient(id);
            if (res) {
                res->stdPrint();
            } else {
                std::cout << "Incorrect id";
            }
            std::cout << "\n";
        }
        if (command == "find_ord") {
            int id;
            std::cin >> id;
            auto res = test.findOrder(id);
            if (res) {
                res->stdPrint();
            } else {
                std::cout << "Incorrect id";
            }
            std::cout << "\n";
        }
        if (command == "book_ord") {
            int id, client_id;
            std::cin >> id >> client_id;
            test.bookOrder(id, client_id);
        }
        if (command == "store") {
            st.storeCompany(test);
        }
        if (command == "exit") {
            return;
        }
        std::cout << "> ";
    }
     */
}