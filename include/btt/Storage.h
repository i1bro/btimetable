#ifndef BTIMETABLE_STORAGE_H
#define BTIMETABLE_STORAGE_H

#include <pqxx/pqxx>
#include <set>
#include <unordered_map>
#include "Entities.h"

namespace db {

enum Tables { clients, employees, orders, companies };

enum column {
    name,
    fullName,
    phoneNumber,
    email,
    title,
    timeStart,
    duration,
    clientId,
    companyId,
    employeeId,
    id,
    all
};

class Operation {
public:
    std::string execute() const;

protected:
    Tables table;
    std::stringstream s;
    bool canBeExecuted = false;

    Operation() = default;

    std::string parseCol(column col);
};

class Update : public Operation {
private:
    bool setUsed = false;
    bool whereUsed = false;

public:
    Update() = delete;

    explicit Update(Tables t);

    Update &set(column col, const std::string &value);

    Update &set(column col, long long value);

    Update &where(column col, const std::string &value);

    Update &where(column col, long long value);
};

class Insert : public Operation {
private:
    std::set<column> requiredCols;
    std::unordered_map<column, std::string> currentValues;

public:
    Insert() = delete;

    explicit Insert(Tables t);

    Insert &set(column col, const std::string &value);

    Insert &set(column col, long long value);
};

class Select : public Operation {
private:
    bool columnsUsed = false;
    bool whereUsed = false;
    bool orderedUsed = false;

public:
    Select() = delete;

    explicit Select(Tables t);

    Select &columns(const std::vector<column> &cols);

    Select &where(column col, const std::string &value);

    Select &where(column col, long long value);

    Select &orderedBy(column col);
};

class Result {
private:
    pqxx::result res;

public:
    Result() = delete;

    explicit Result(const pqxx::result &res_);

    Result &operator=(const pqxx::result &res_);

    explicit Result(pqxx::result &&res_);

    Result &operator=(pqxx::result &&res_);

    ~Result() = default;

    Employee toEmployee();

    Client toClient();

    Order toOrder();

    Company toCompany();

    long long toLL();

    std::vector<long long> toVecLL();
};

class Storage {
private:
    pqxx::connection C{
        "host=localhost "
        "port=5432 "
        "user=bttsu "
        "password=ihatepostgresql "
        "dbname=bttdb"};

    Result execute(const Operation &op);

public:
    Storage() = default;

    long long createCompany(const std::string &name);

    long long createOrder(long long companyId,
                          const std::string &title,
                          const std::string &timeStart,
                          const std::string &duration,
                          long long employeeId);

    long long createEmployee(long long companyId, const std::string &fullName);

    long long createClient(const std::string &fullName,
                           const std::string &phoneNumber,
                           const std::string &email);

    void storeEmployee(const Employee &employee);

    void storeClient(const Client &client);

    void storeOrder(const Order &order);

    void storeCompany(const Company &company);

    Employee getEmployeeById(long long id);

    Client getClientById(long long id);

    Order getOrderById(long long id);

    Company getCompanyById(long long id);

    void deleteEmployee(long long id);

    void deleteClient(long long id);

    void deleteOrder(long long id);

    void deleteCompany(long long id);

    std::vector<long long> listVacantOrdersOfCompany(long long employeeId);

    std::vector<long long> listBookedOrdersOfCompany(long long employeeId);

    std::vector<long long> listVacantOrdersOfEmployee(long long employeeId);

    std::vector<long long> listBookedOrdersOfEmployee(long long employeeId);

    std::vector<long long> listOrdersOfClient(long long clientId);

    std::vector<long long> listCompanies();

    std::vector<long long> listEmployeesOfCompany(long long id);
};

}  // namespace db

#endif  // BTIMETABLE_STORAGE_H
