#ifndef BTIMETABLE_ENTITIES_H
#define BTIMETABLE_ENTITIES_H

#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <map>
#include <memory>

namespace dataBase {

    template<typename T>
    class Holder {
    private:
        std::map<int, std::shared_ptr<T>> id_map;
        std::vector<std::shared_ptr<T>> elements;
    public:
        Holder() = default;

        void add(T value);

        std::shared_ptr<T> findById(int id);

        [[nodiscard]] const std::vector<std::shared_ptr<T>> &listElements();

        void removeById(int id);
    };

    class Employee {
    private:

    public:
        const int id = 0;
        const std::string full_name;

        Employee() = default;

        Employee(int id_, std::string full_name_) : id(id_), full_name(std::move(full_name_)) {}

        void stdPrint() const;
    };

    class Client {
    private:

    public:
        const int id = 0;
        const std::string full_name;

        Client() = default;

        Client(int id_, std::string full_name_) : id(id_), full_name(std::move(full_name_)) {}

        void stdPrint() const;
    };

    class Order {
    private:

    public:
        const int id = 0, time_start = 0, duration = 0;
        const std::shared_ptr<Client> client;
        const std::shared_ptr<Employee> employee;

        Order() = default;

        Order(int id_, int time_start_, int duration_, std::shared_ptr<Client> client_,
              std::shared_ptr<Employee> employee_) : id(id_),
                                                   time_start(time_start_),
                                                   duration(duration_),
                                                   client(std::move(client_)),
                                                   employee(std::move(employee_)) {}

        void stdPrint() const;
    };

    class Schedule {
    private:
        Holder<Order> orders;
    public:
        Schedule() = default;

        void addOrder(int id_, int time_start_, int duration_, std::shared_ptr<Client> client_, std::shared_ptr<Employee> employee_);

        std::shared_ptr<Order> findOrder(int id);

        [[nodiscard]] const std::vector<std::shared_ptr<Order>> &listOrders();

        void deleteOrder(int id);
    };

    class Company {
    private:
        Holder<Employee> employees;
        Holder<Client> clients;
        Schedule schedule;
    public:
        const std::string name;

        Company() = default;

        explicit Company(std::string name_) : name(std::move(name_)) {}

        void addEmployee(int id_, std::string full_name_);

        std::shared_ptr<Employee> findEmployee(int id);

        [[nodiscard]] const std::vector<std::shared_ptr<Employee>> &listEmployees();

        void deleteEmployee(int id);

        void addClient(int id_, std::string full_name_);

        std::shared_ptr<Client> findClient(int id);

        [[nodiscard]] const std::vector<std::shared_ptr<Client>> &listClients();

        void deleteClient(int id);

        void addOrder(int id_, int time_start_, int duration_, int client_id, int employee_id);

        std::shared_ptr<Order> findOrder(int id);

        [[nodiscard]] const std::vector<std::shared_ptr<Order>> &listOrders();

        void deleteOrder(int id);
    };

}
#endif //BTIMETABLE_ENTITIES_H