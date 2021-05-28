#ifndef BTIMETABLE_ENTITIES_H
#define BTIMETABLE_ENTITIES_H

#include <exception>
#include <stdexcept>
#include <string>

namespace db {

struct bttError : std::runtime_error {
    explicit bttError(const std::string &m) : std::runtime_error(m) {
    }
};

struct bttFatalError : bttError {
    explicit bttFatalError(const std::string &m) : bttError(m) {
    }
};

enum sortParam { byRating, byName, byTimeStart, byDuration };

class Employee {
public:
    const long long id;
    long long companyId;
    std::string fullName;
    double rating;
    long long ratingCnt;
    bool isDeleted;

    Employee(long long id_,
             long long companyId_,
             std::string fullName_,
             double rating_,
             long long ratingCnt_,
             bool isDeleted_)
        : id(id_),
          companyId(companyId_),
          fullName(std::move(fullName_)),
          rating(rating_),
          ratingCnt(ratingCnt_),
          isDeleted(isDeleted_) {
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

struct orderSearchParams {
    long long companyId = -1;
    long long employeeId = -1;
    sortParam sorted = byTimeStart;
    std::string title;
    long long minTimeStart = 0;
    long long maxTimeStart = -1;
    long long minDuration = 0;
    long long maxDuration = -1;
};

}  // namespace db
#endif  // BTIMETABLE_ENTITIES_H