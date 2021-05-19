#ifndef BTIMETABLE_STORAGE_H
#define BTIMETABLE_STORAGE_H

#include <pqxx/pqxx>
#include <set>
#include <vector>
#include <array>
#include <unordered_map>
#include "Entities.h"

namespace db {

enum Table { clients, employees, orders, companies };

enum Column {
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
    Table table;
    std::stringstream s;
    bool canBeExecuted = false;

    Operation() = default;

    std::string parseCol(Column col);
};

class Update : public Operation {
private:
    bool setUsed = false;
    bool whereUsed = false;

public:
    Update() = delete;

    explicit Update(Table t);

    Update &set(Column col, const std::string &value);

    Update &set(Column col, long long value);

    Update &where(Column col, const std::string &value);

    Update &where(Column col, long long value);
};

class Insert : public Operation {
private:
    std::set<Column> requiredCols;
    std::unordered_map<Column, std::string> currentValues;

public:
    Insert() = delete;

    explicit Insert(Table t);

    Insert &set(Column col, const std::string &value);

    Insert &set(Column col, long long value);
};

class Select : public Operation {
private:
    bool columnsUsed = false;
    bool whereUsed = false;
    bool orderedUsed = false;

public:
    Select() = delete;

    explicit Select(Table t);

    Select &columns(const std::vector<Column> &cols);

    Select &where(Column col, const std::string &value);

    Select &where(Column col, long long value);

    Select &orderedBy(Column col);
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

public:
    Result execute(const Operation &op);

    Storage() = default;
};

}  // namespace db

#endif  // BTIMETABLE_STORAGE_H