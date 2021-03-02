#ifndef BTIMETABLE_ENTITIES_H
#define BTIMETABLE_ENTITIES_H

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace dataBase {

template <typename T>
class Holder {
private:
    std::map<int, std::shared_ptr<T>> idMap;
    std::vector<std::shared_ptr<T>> elements;

public:
    Holder() = default;

    void add(T value);

    void addByPtr(std::shared_ptr<T> elementPtr);

    std::shared_ptr<T> findById(int id);

    [[nodiscard]] const std::vector<std::shared_ptr<T>> &listElements();

    void removeById(int id);
};

class Employee {
private:
public:
    const int id = 0;
    std::string fullName;

    Employee() = default;

    Employee(int id_, std::string fullName_)
        : id(id_), fullName(std::move(fullName_)) {
    }

    void stdPrint() const;
};

class Client {
private:
public:
    const int id = 0;
    std::string fullName;

    Client() = default;

    Client(int id_, std::string fullName_)
        : id(id_), fullName(std::move(fullName_)) {
    }

    void stdPrint() const;
};

class Order {
private:
public:
    const int id = 0;
    std::string title;
    int timeStart = 0;
    int duration = 0;
    int clientId = -1;
    int employeeId = -1;

    Order() = default;

    Order(int id_,
          std::string title_,
          int timeStart_,
          int duration_,
          int clientId_,
          int employeeId_)
        : id(id_),
          title(std::move(title_)),
          timeStart(timeStart_),
          duration(duration_),
          clientId(clientId_),
          employeeId(employeeId_) {
    }

    Order(int id_,
          std::string title_,
          int timeStart_,
          int duration_,
          int employeeId_)
        : id(id_),
          title(std::move(title_)),
          timeStart(timeStart_),
          duration(duration_),
          employeeId(employeeId_) {
    }

    void stdPrint() const;
};

class Schedule {
private:
    Holder<Order> vacantOrders;
    Holder<Order> bookedOrders;

public:
    Schedule() = default;

    void addOrder(int id,
                  std::string title,
                  int timeStart,
                  int duration,
                  int employeeId);

    std::shared_ptr<Order> findOrder(int id);

    [[nodiscard]] const std::vector<std::shared_ptr<Order>> &listVacantOrders();

    [[nodiscard]] const std::vector<std::shared_ptr<Order>> &listBookedOrders();

    void bookOrder(int id, int clientId);

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

    explicit Company(std::string name_) : name(std::move(name_)) {
    }

    void addEmployee(std::string fullName);

    std::shared_ptr<Employee> findEmployee(int id);

    [[nodiscard]] const std::vector<std::shared_ptr<Employee>> &listEmployees();

    void deleteEmployee(int id);

    void addClient(std::string fullName);

    std::shared_ptr<Client> findClient(int id);

    [[nodiscard]] const std::vector<std::shared_ptr<Client>> &listClients();

    void deleteClient(int id);

    void addOrder(std::string title,
                  int timeStart,
                  int duration,
                  int employeeId);

    std::shared_ptr<Order> findOrder(int id);

    [[nodiscard]] const std::vector<std::shared_ptr<Order>> &listVacantOrders();

    [[nodiscard]] const std::vector<std::shared_ptr<Order>> &listBookedOrders();

    void bookOrder(int id, int clientId);

    void deleteOrder(int id);

    [[nodiscard]] int getLastEmployeeId() const;

    [[nodiscard]] int getLastClientId() const;

    [[nodiscard]] int getLastOrderId() const;
};

}  // namespace dataBase
#endif  // BTIMETABLE_ENTITIES_H