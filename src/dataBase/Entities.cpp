#include "Entities.h"

namespace dataBase {
    void Company::addEmployee(int id_, std::string full_name_) {
        employees.push_back(Employee(id_, std::move(full_name_)));
    }

    void Company::addClient(int id_, std::string full_name_) {
        clients.push_back(Client(id_, std::move(full_name_)));
    }

    void Company::stdPrintEmployees() {
        std::cout << "employees:{\n";
        for(auto& i: employees) {
            i.stdPrint();
            std::cout << "\n";
        }
        std::cout << "}" << "\n";
    }

    void Company::stdPrintClients() {
        std::cout << "clients:{\n";
        for(auto& i: clients) {
            i.stdPrint();
            std::cout << "\n";
        }
        std::cout << "}" << "\n";
    }

    void Schedule::addOrder(int id_, int time_start_, int time_end_, Client *client_, Employee *employee_) {
        orders.push_back(Order(id_, time_start_, time_end_, client_, employee_));
    }

    void Schedule::stdPrint() {
        std::cout << "Schedule:{\n";
        for(auto& i: orders) {
            i.stdPrint();
        }
        std::cout << "}" << "\n";
    }

    void Employee::stdPrint() {
        std::cout << "Employee:{" << id << ", " << full_name << "} ";
    }

    void Client::stdPrint() {
        std::cout << "Client:{" << id << ", " << full_name << "} ";
    }

    void Order::stdPrint() {
        std::cout << "Order:{" << id << ", " << time_start << ", " << time_end << ", ";
        client->stdPrint();
        employee->stdPrint();
        std::cout << "}" << std::endl;
    }
}

