#ifndef BTIMETABLE_STORAGE_H
#define BTIMETABLE_STORAGE_H

#ifndef BTT_CONNECTION_STRING
#define BTT_CONNECTION_STRING "host=retired.tk port=58974 user=postgres password=T38ssGHzjcRviche7ex dbname=postgres"
#endif

#include <exception>
#include <pqxx/pqxx>
#include <unordered_map>
#include <vector>
#include "Entities.h"

namespace db {

struct buildingQueryError : bttError {
    buildingQueryError()
        : bttError("This is a bug for sure. Please message me what did you do to get this exception.") {
    }
};

struct processingQueryError : bttError {
    processingQueryError()
        : bttError("pqxx thrown an exception while processing query. Input might be "
                    "corrupted. This error shouldn't have reached user's eyes.") {
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

    Update &set(Column col, bool value);

    Update &set(Column col, long long value);

    Update &setNull(Column col);

    Update &where(Column col, const std::string &value);

    Update &where(Column col, bool value);

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

    Select &where(Column col, bool value);

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

    size_t size();

    Employee toEmployee(size_t ind = 0);

    Client toClient(size_t ind = 0);

    Order toOrder(size_t ind = 0);

    Company toCompany(size_t ind = 0);

    long long toLL();

    std::vector<long long> toVecLL();
};

class Storage {
private:
    pqxx::connection C{BTT_CONNECTION_STRING};

public:
    Result execute(Operation &op);

    Result execute(pqxx::work &W, Operation &op);

    pqxx::work startWork();

    Storage() = default;
};

}  // namespace db

#endif  // BTIMETABLE_STORAGE_H