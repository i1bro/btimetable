#include "btt/Storage.h"
#include <iostream>

namespace db {
namespace {
const std::string &nameOfTable(Table t) {
    static std::unordered_map<Table, const std::string> nameOfTable = {
        {tblClients, "clients"},
        {tblEmployees, "employees"},
        {tblOrders, "orders"},
        {tblCompanies, "companies"},
        {tblClientAccounts, "client_accounts"},
        {tblCompanyAccounts, "company_accounts"}};
    return nameOfTable[t];
};

const std::string &nameOfColumn(Column col) {
    static std::unordered_map<Column, const std::string> nameOfColumn = {
        {clmName, "name"},
        {clmFullName, "full_name"},
        {clmPhoneNumber, "phone_number"},
        {clmEmail, "email"},
        {clmTitle, "title"},
        {clmTimeStart, "time_start"},
        {clmDuration, "duration"},
        {clmClientId, "client_id"},
        {clmCompanyId, "company_id"},
        {clmEmployeeId, "employee_id"},
        {clmId, "id"},
        {clmRating, "rating"},
        {clmRatingSum, "rating_sum"},
        {clmRatingCnt, "rating_cnt"},
        {clmStatus, "status"},
        {clmIsDeleted, "is_deleted"},
        {clmPassword, "password"},
        {clmAll, "*"}};
    return nameOfColumn[col];
};

bool isIn(Column col, const std::vector<Column> &cols) {
    for (auto c : cols) {
        if (col == c) {
            return true;
        }
    }
    return false;
}
}  // namespace

Update::Update(Table t) {
    table = t;
}

std::string Update::build() {
    if (values.empty()) {
        throw buildingQueryError();
    }
    std::stringstream s;
    s << "UPDATE " << nameOfTable(table) << " SET";
    bool beg = true;
    for (auto &val : values) {
        if (!beg) {
            s << ",";
        }
        beg = false;
        s << " " << nameOfColumn(val.first) << " = " << val.second;
    }
    if (!conditions.empty()) {
        s << " WHERE";
        beg = true;
        for (auto &val : conditions) {
            if (!beg) {
                s << " AND";
            }
            beg = false;
            s << " " << nameOfColumn(val.first) << val.second;
        }
    }
    return s.str();
}

Update &Update::set(Column col, const std::string &value) {
    values.emplace_back(col, "'" + value + "'");
    return *this;
}

Update &Update::set(Column col, long long value) {
    values.emplace_back(col, std::to_string(value));
    return *this;
}

Update &Update::set(Column col, bool value) {
    values.emplace_back(col, std::string{(value ? "TRUE" : "FALSE")});
    return *this;
}

Update &Update::setNull(Column col) {
    values.emplace_back(col, "NULL");
    return *this;
}

Update &Update::where(Column col, const std::string &value) {
    conditions.emplace_back(col, " = '" + value + "'");
    return *this;
}

Update &Update::where(Column col, bool value) {
    conditions.emplace_back(col,
                            " = " + std::string{(value ? "TRUE" : "FALSE")});
    return *this;
}

Update &Update::where(Column col, long long value, const std::string &op) {
    if (op != "=" && op != ">" && op != "<" && op != ">=" && op != "<=" &&
        op != "!=") {
        throw buildingQueryError();
    }
    conditions.emplace_back(col, " " + op + " " + std::to_string(value));
    return *this;
}

Update &Update::whereIsNull(Column col) {
    conditions.emplace_back(col, " IS NULL");
    return *this;
}

Update &Update::whereIsNotNull(Column col) {
    conditions.emplace_back(col, " IS NOT NULL");
    return *this;
}

std::string Insert::build() {
    if (values.empty()) {
        throw buildingQueryError();
    }
    std::stringstream s;
    s << "INSERT INTO " << nameOfTable(table) << "(";
    bool beg = true;
    for (auto &val : values) {
        if (!beg) {
            s << ",";
        }
        beg = false;
        s << " " << nameOfColumn(val.first);
    }
    s << ") VALUES (";
    beg = true;
    for (auto &val : values) {
        if (!beg) {
            s << ",";
        }
        beg = false;
        s << " " << val.second;
    }
    s << ")";
    if (returnCol != clmAll) {
        s << " RETURNING " << nameOfColumn(returnCol);
    }
    return s.str();
}

Insert::Insert(Table t) {
    table = t;
}

Insert &Insert::set(Column col, const std::string &value) {
    values.emplace_back(col, "'" + value + "'");
    return *this;
}

Insert &Insert::set(Column col, long long value) {
    values.emplace_back(col, std::to_string(value));
    return *this;
}

Insert &Insert::setNull(Column col) {
    values.emplace_back(col, "NULL");
    return *this;
}

Insert &Insert::returning(Column col) {
    returnCol = col;
    return *this;
}

std::string Select::build() {
    if (cols.empty()) {
        throw buildingQueryError();
    }
    std::stringstream s;
    s << "SELECT ";
    bool beg = true;
    for (auto &val : cols) {
        if (!beg) {
            s << ",";
        }
        beg = false;
        s << " " << nameOfColumn(val);
    }
    s << " FROM " << nameOfTable(table);
    if (!conditions.empty()) {
        s << " WHERE";
        beg = true;
        for (auto &val : conditions) {
            if (!beg) {
                s << " AND";
            }
            beg = false;
            s << " " << nameOfColumn(val.first) << val.second;
        }
    }
    if (!orderStr.empty()) {
        s << " ORDER BY";
        beg = true;
        for (auto &val : orderStr) {
            if (!beg) {
                s << ",";
            }
            beg = false;
            s << " " << val;
        }
    }
    return s.str();
}

Select::Select(Table t) {
    table = t;
}

Select &Select::columns(const std::vector<Column> &cols_) {
    for (auto c : cols_) {
        cols.push_back(c);
    }
    return *this;
}

Select &Select::where(Column col, const std::string &value) {
    conditions.emplace_back(col, " = '" + value + "'");
    return *this;
}

Select &Select::where(Column col, bool value) {
    conditions.emplace_back(col,
                            " = " + std::string{(value ? "TRUE" : "FALSE")});
    return *this;
}

Select &Select::where(Column col, long long value, const std::string &op) {
    if (op != "=" && op != ">" && op != "<" && op != ">=" && op != "<=" &&
        op != "!=") {
        throw buildingQueryError();
    }
    conditions.emplace_back(col, " " + op + " " + std::to_string(value));
    return *this;
}

Select &Select::whereIsNull(Column col) {
    conditions.emplace_back(col, " IS NULL");
    return *this;
}

Select &Select::whereIsNotNull(Column col) {
    conditions.emplace_back(col, " IS NOT NULL");
    return *this;
}

Select &Select::orderedBy(Column col, bool reversed) {
    if (!reversed) {
        orderStr.push_back(nameOfColumn(col) + " ASC");
    } else {
        orderStr.push_back(nameOfColumn(col) + " DESC");
    }
    return *this;
}

Select &Select::orderedBy(const std::string &condition) {
    orderStr.push_back(condition);
    return *this;
}

Result::Result(const pqxx::result &res_) {
    res = res_;
}

Result &Result::operator=(const pqxx::result &res_) {
    res = res_;
    return *this;
}

Result::Result(pqxx::result &&res_) {
    res = res_;
}

Result &Result::operator=(pqxx::result &&res_) {
    res = res_;
    return *this;
}

Employee Result::toEmployee() {
    const pqxx::row &cur = res[0];
    double rating = 0;
    if (cur["rating_cnt"].as<long long>() != 0) {
        rating =
            cur["rating_sum"].as<double>() / cur["rating_cnt"].as<double>();
    }
    Employee employee(
        cur["id"].as<long long>(), cur["company_id"].as<long long>(),
        cur["full_name"].c_str(), rating, cur["rating_cnt"].as<long long>(),
        cur["is_deleted"].as<bool>());
    return employee;
}

Client Result::toClient() {
    const pqxx::row &cur = res[0];
    Client client(cur["id"].as<long long>(), cur["full_name"].c_str(),
                  cur["phone_number"].c_str(), cur["email"].c_str());
    return client;
}

Order Result::toOrder() {
    const pqxx::row &cur = res[0];
    Order order(
        cur["id"].as<long long>(), cur["company_id"].as<long long>(),
        cur["title"].c_str(), cur["time_start"].as<long long>(),
        cur["duration"].as<long long>(),
        (cur["client_id"].is_null() ? -1 : cur["client_id"].as<long long>()),
        cur["employee_id"].as<long long>(),
        static_cast<Order::statusEnum>(cur["status"].as<int>()),
        cur["rating"].as<int>());
    return order;
}

Company Result::toCompany() {
    const pqxx::row &cur = res[0];
    double rating = 0;
    if (cur["rating_cnt"].as<long long>() != 0) {
        rating =
            cur["rating_sum"].as<double>() / cur["rating_cnt"].as<double>();
    }
    Company company(cur["id"].as<long long>(), cur["name"].c_str(), rating,
                    cur["rating_cnt"].as<long long>());
    return company;
}

long long Result::toLL() {
    return res[0][0].as<long long>();
}

std::vector<long long> Result::toVecLL() {
    std::vector<long long> ans;
    for (auto &&re : res) {
        ans.push_back(re["id"].as<long long>());
    }
    return ans;
}

Result Storage::execute(Operation &op) {
    try {
        pqxx::work W{C};
        auto a = op.build();
        Result res(W.exec(op.build()));
        W.commit();
        return res;
    } catch (const std::exception &e) {
        std::cerr << e.what();
        throw e;
    }
}

}  // namespace db