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

        void addByPtr(std::shared_ptr<T> element_ptr);

        std::shared_ptr<T> findById(int id);

        [[nodiscard]] const std::vector<std::shared_ptr<T>> &listElements();

        void removeById(int id);
    };

    class Employee {
    private:

    public:
        const int id = 0;
        std::string full_name;

        Employee() = default;

        Employee(int id_, std::string full_name_) : id(id_), full_name(std::move(full_name_)) {}

        void stdPrint() const;
    };

    class Client {
    private:

    public:
        const int id = 0;
        std::string full_name;

        Client() = default;

        Client(int id_, std::string full_name_) : id(id_), full_name(std::move(full_name_)) {}

        void stdPrint() const;
    };

    class Order {
    private:

    public:
        const int id = 0;
        int time_start = 0;
        int duration = 0;
        int client_id = -1;
        int employee_id = -1;

        Order() = default;

        Order(int id_, int time_start_, int duration_, int client_id_, int employee_id_) : id(id_),
                                                                                           time_start(time_start_),
                                                                                           duration(duration_),
                                                                                           client_id(client_id_),
                                                                                           employee_id(employee_id_) {}

        Order(int id_, int time_start_, int duration_, int employee_id_) : id(id_),
                                                                           time_start(time_start_),
                                                                           duration(duration_),
                                                                           employee_id(employee_id_) {}

        void stdPrint() const;
    };

    class Schedule {
    private:
        Holder<Order> vacant_orders;
        Holder<Order> booked_orders;
    public:
        Schedule() = default;

        void addOrder(int id, int time_start, int duration, int employee_id);

        std::shared_ptr<Order> findOrder(int id);

        [[nodiscard]] const std::vector<std::shared_ptr<Order>> &listVacantOrders();

        [[nodiscard]] const std::vector<std::shared_ptr<Order>> &listBookedOrders();

        void bookOrder(int id, int client_id);

        void deleteOrder(int id);
    };

    class Company {
    private:
        Holder<Employee> employees;
        Holder<Client> clients;
        Schedule schedule;
        int lastEmployeeId = 0;
        int lastClientId = 0;
        int lastOrderId = 0;
    public:
        std::string name;

        Company() = default;

        explicit Company(std::string name_) : name(std::move(name_)) {}

        void addEmployee(std::string full_name);

        std::shared_ptr<Employee> findEmployee(int id);

        [[nodiscard]] const std::vector<std::shared_ptr<Employee>> &listEmployees();

        void deleteEmployee(int id);

        void addClient(std::string full_name);

        std::shared_ptr<Client> findClient(int id);

        [[nodiscard]] const std::vector<std::shared_ptr<Client>> &listClients();

        void deleteClient(int id);

        void addOrder(int time_start, int duration, int employee_id);

        std::shared_ptr<Order> findOrder(int id);

        [[nodiscard]] const std::vector<std::shared_ptr<Order>> &listVacantOrders();

        [[nodiscard]] const std::vector<std::shared_ptr<Order>> &listBookedOrders();

        void bookOrder(int id, int client_id);

        void deleteOrder(int id);

        [[nodiscard]] int getLastEmployeeId() const;

        [[nodiscard]] int getLastClientId() const;

        [[nodiscard]] int getLastOrderId() const;
    };

}
#endif //BTIMETABLE_ENTITIES_H