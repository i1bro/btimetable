#ifndef BTIMETABLE_ENTITIES_H
#define BTIMETABLE_ENTITIES_H

#include <string>
#include <utility>
#include <vector>

namespace db {

enum sortParam {
    byId,
    byTimeStart,
    byDuration,
    byCompanyRating,
    byEmployeeRating,
    byCompanyName,
    byEmployeeName
};

class Employee {
public:
    const long long id;
    long long companyId;
    std::string fullName;
    double rating;
    long long ratingCnt;

    Employee(long long id_,
             long long companyId_,
             std::string fullName_,
             double rating_,
             long long ratingCnt_)
        : id(id_),
          companyId(companyId_),
          fullName(std::move(fullName_)),
          rating(rating_),
          ratingCnt(ratingCnt_) {
    }
};

class Client {
public:
    const long long id;
    std::string fullName;
    std::string phoneNumber;
    std::string email;

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
public:
    enum statusEnum { vacant = 0, deleted = -1, booked = 1 };

    const long long id;
    long long companyId;
    std::string title;
    long long timeStart;
    long long duration;
    long long clientId;
    long long employeeId;
    statusEnum status = vacant;
    int rating;

    Order(long long id_,
          long long companyId_,
          std::string title_,
          long long timeStart_,
          long long duration_,
          long long employeeId_,
          statusEnum status_,
          int rating_)
        : id(id_),
          companyId(companyId_),
          title(std::move(title_)),
          timeStart(timeStart_),
          duration(duration_),
          employeeId(employeeId_),
          status(status_),
          rating(rating_) {
    }

    Order(long long id_,
          long long companyId_,
          std::string title_,
          long long timeStart_,
          long long duration_,
          long long clientId_,
          long long employeeId_,
          statusEnum status_,
          int rating_)
        : id(id_),
          companyId(companyId_),
          title(std::move(title_)),
          timeStart(timeStart_),
          duration(duration_),
          clientId(clientId_),
          employeeId(employeeId_),
          status(status_),
          rating(rating_) {
    }
};

class Company {
public:
    const long long id;
    std::string name;
    double rating;
    long long ratingCnt;

    Company(long long id_,
            std::string name_,
            double rating_,
            long long ratingCnt_)
        : id(id_),
          name(std::move(name_)),
          rating(rating_),
          ratingCnt(ratingCnt_) {
    }
};

}  // namespace db
#endif  // BTIMETABLE_ENTITIES_H