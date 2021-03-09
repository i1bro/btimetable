#ifndef BTIMETABLE_ENTITIES_H
#define BTIMETABLE_ENTITIES_H

#include <string>
#include <vector>

namespace dataBase {

class Employee {
private:
public:
    const long long id = 0;
    std::string fullName;

    explicit Employee(long long id_) : id(id_) {
    }

    Employee(long long id_, std::string fullName_)
        : id(id_), fullName(std::move(fullName_)) {
    }
};

class Client {
private:
public:
    const long long id = 0;
    std::string fullName;

    explicit Client(long long id_) : id(id_) {
    }

    Client(long long id_, std::string fullName_)
        : id(id_), fullName(std::move(fullName_)) {
    }
};

class Order {
private:
public:
    const long long id = 0;
    std::string title;
    int timeStart = -1;
    int duration = -1;
    int clientId = -1;
    int employeeId = -1;

    explicit Order(long long id_) : id(id_) {
    }

    Order(long long id_,
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

    Order(long long id_,
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
};

class Schedule {
private:
    std::vector<long long> vacantOrders;
    std::vector<long long> bookedOrders;

public:
    Schedule() = default;

    void addVacantOrder(long long id);

    void addBookedOrder(long long id);

    [[nodiscard]] const std::vector<long long> &listVacantOrders() const;

    [[nodiscard]] const std::vector<long long> &listBookedOrders() const;

    void deleteOrder(long long id);
};

class Company {
private:
    std::vector<long long> employees;
    Schedule schedule;

public:
    const std::string name;

    explicit Company(std::string name_) : name(std::move(name_)) {
    }

    void addEmployee(long long id);

    [[nodiscard]] const std::vector<long long> &listEmployees() const;

    void deleteEmployee(long long id);

    void addVacantOrder(long long id);

    void addBookedOrder(long long id);

    [[nodiscard]] const std::vector<long long> &listVacantOrders() const;

    [[nodiscard]] const std::vector<long long> &listBookedOrders() const;

    void deleteOrder(long long id);

    [[nodiscard]] const Schedule &getSchedule() const;
};

}  // namespace dataBase
#endif  // BTIMETABLE_ENTITIES_H