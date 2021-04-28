#ifndef BTIMETABLE_ENTITIES_H
#define BTIMETABLE_ENTITIES_H

#include <string>
#include <utility>
#include <vector>

namespace dataBase {

class Employee {
private:
public:
    const long long id = 0;
    long long companyId = 0;
    std::string fullName;

    explicit Employee(long long id_) : id(id_) {
    }

    Employee(long long id_, long long companyId_, std::string fullName_)
        : id(id_), companyId(companyId_), fullName(std::move(fullName_)) {
    }
};

class Client {
private:
public:
    const long long id = 0;
    std::string fullName;
    std::string phoneNumber;
    std::string email;

    explicit Client(long long id_) : id(id_) {
    }

    Client(long long id_,
           std::string fullName_,
           std::string phoneNumber_,
           std::string email_)
        : id(id_),
          fullName(std::move(fullName_)),
          phoneNumber(std::move(phoneNumber_)),
          email(std::move(email_)) {
    }
};

class Order {
private:
public:
    const long long id = 0;
    long long companyId = 0;
    std::string title;
    long long timeStart = -1;
    long long duration = -1;
    long long clientId = -1;
    long long employeeId = -1;

    explicit Order(long long id_) : id(id_) {
    }

    Order(long long id_,
          long long companyId_,
          std::string title_,
          long long timeStart_,
          long long duration_,
          long long clientId_,
          long long employeeId_)
        : id(id_),
          companyId(companyId_),
          title(std::move(title_)),
          timeStart(timeStart_),
          duration(duration_),
          clientId(clientId_),
          employeeId(employeeId_) {
    }

    Order(long long id_,
          long long companyId_,
          std::string title_,
          long long timeStart_,
          long long duration_,
          long long employeeId_)
        : id(id_),
          companyId(companyId_),
          title(std::move(title_)),
          timeStart(timeStart_),
          duration(duration_),
          employeeId(employeeId_) {
    }
};

class Company {
private:
public:
    const long long id = 0;
    std::string name;

    explicit Company(long long id_) : id(id_) {
    }

    explicit Company(long long id_, std::string name_)
        : id(id_), name(std::move(name_)) {
    }
};

}  // namespace dataBase
#endif  // BTIMETABLE_ENTITIES_H