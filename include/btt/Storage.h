#ifndef BTIMETABLE_STORAGE_H
#define BTIMETABLE_STORAGE_H

#include <exception>
#include <pqxx/pqxx>
#include <unordered_map>
#include <vector>
#include "Entities.h"

namespace db {

struct buildingQueryError : std::runtime_error {
    buildingQueryError()
        : std::runtime_error(
              "Please message me what did you do to get this exception") {
    }
};

struct processingQueryError : std::runtime_error {
    processingQueryError()
        : std::runtime_error(
              "pqxx thrown an exception while processing query. Input might be "
              "corrupted") {
    }
};

enum Table {
    tblClients,
    tblEmployees,
    tblOrders,
    tblCompanies,
    tblClientAccounts,
    tblCompanyAccounts
};

enum Column {
    clmName,
    clmFullName,
    clmPhoneNumber,
    clmEmail,
    clmTitle,
    clmTimeStart,
    clmDuration,
    clmClientId,
    clmCompanyId,
    clmEmployeeId,
    clmId,
    clmPassword,
    clmRating,
    clmRatingSum,
    clmRatingCnt,
    clmStatus,
    clmIsDeleted,
    clmAll
};

class Operation {
public:
    virtual std::string build() = 0;

protected:
    Table table;
};

class Update : public Operation {
private:
    std::vector<std::pair<Column, std::string>> values, conditions;

public:
    Update() = delete;

    std::string build() override;

    explicit Update(Table t);

    Update &set(Column col, const std::string &value);

    Update &set(Column col, long long value);

    Update &setNull(Column col);

    Update &where(Column col, const std::string &value);

    Update &where(Column col, long long value, const std::string &op = "=");

    Update &whereIsNull(Column col);

    Update &whereIsNotNull(Column col);
};

class Insert : public Operation {
private:
    std::vector<std::pair<Column, std::string>> values;
    Column returnCol = clmAll;

public:
    Insert() = delete;

    std::string build() override;

    explicit Insert(Table t);

    Insert &set(Column col, const std::string &value);

    Insert &set(Column col, long long value);

    Insert &setNull(Column col);

    Insert &returning(Column col);
};

class Select : public Operation {
private:
    std::vector<Column> cols;
    std::vector<std::pair<Column, std::string>> conditions;
    std::vector<std::string> orderStr;

public:
    Select() = delete;

    std::string build() override;

    explicit Select(Table t);

    Select &columns(const std::vector<Column> &cols_);

    Select &where(Column col, const std::string &value);

    Select &where(Column col, long long value, const std::string &op = "=");

    Select &whereIsNull(Column col);

    Select &whereIsNotNull(Column col);

    Select &orderedBy(Column col, bool reversed = false);

    Select &orderedBy(const std::string &condition);
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
        "host=retired.tk "
        "port=58974 "
        "user=postgres "
        "password=T38ssGHzjcRviche7ex "
        "dbname=postgres"};

public:
    Result execute(Operation &op);

    Storage() = default;
};

}  // namespace db

#endif  // BTIMETABLE_STORAGE_H