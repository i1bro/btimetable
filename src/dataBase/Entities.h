#ifndef BTIMETABLE_ENTITIES_H
#define BTIMETABLE_ENTITIES_H

#include <string>
#include <vector>
#include <iostream>

namespace dataBase {

    class Employee {
    private:

    public:
        int id = 0;
        std::string full_name;

        Employee() = default;
        Employee(int id_, std::string full_name_) : id(id_), full_name(std::move(full_name_)) {}

        void stdPrint();
    };

    class Client {
    private:

    public:
        int id = 0;
        std::string full_name;

        Client() = default;
        Client(int id_, std::string full_name_) : id(id_), full_name(std::move(full_name_)) {}

        void stdPrint();
    };

    class Order {
    private:

    public:
        int id = 0, time_start = 0, time_end = 0;
        Client *client = nullptr;
        Employee *employee = nullptr;

        Order() = default;
        Order(int id_, int time_start_, int time_end_, Client *client_, Employee *employee_) : id(id_),
                                                                                           time_start(time_start_),
                                                                                           time_end(time_end_),
                                                                                           client(client_),
                                                                                           employee(employee_) {}

        void stdPrint();
    };

    class Schedule {
    private:
        std::vector<Order> orders;
    public:
        Schedule() = default;

        void addOrder(int id_, int time_start_, int time_end_, Client *client_, Employee *employee_);
        //void deleteOrder(int id);
        void stdPrint();
    };

    class Company {
    private:
        std::vector<Employee> employees;
        std::vector<Client> clients;
    public:
        std::string name;
        Schedule schedule;

        Company() = default;

        Company(std::string name_) : name(std::move(name_)) {}

        void addEmployee(int id_, std::string full_name_);
        //void deleteEmployee(int id);
        void addClient(int id_, std::string full_name_);
        //void deleteClient(int id);
        void stdPrintEmployees();
        void stdPrintClients();
    };

}
#endif //BTIMETABLE_ENTITIES_H
