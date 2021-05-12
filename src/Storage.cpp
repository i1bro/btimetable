#include "btt/Storage.h"
#include <iostream>

namespace db {

namespace {
const std::vector<Column> stringColumns = {name,
                                           fullName,
                                           phoneNumber,
                                           email,
                                           title,
                                           timeStart,
                                           duration};

const std::vector<Column> numericColumns = {id,
                                            clientId,
                                            companyId,
                                            employeeId};

std::unordered_map<Table, const std::string> nameOfTable = {
        {clients, "clients"},
        {employees, "employees"},
        {orders, "orders"},
        {companies, "companies"}
};

std::unordered_map<Table, const std::vector<Column>> columnsOfTable = {
        {clients, {id,
                        fullName,
                        phoneNumber,
                        email}},
        {employees, {id,
                     companyId,
                     fullName}},
        {orders, {id,
                  companyId,
                          title,
                          duration,
                          timeStart,
                          clientId,
                          employeeId}},
        {companies, {id, name}}
};

std::unordered_map<Column, const std::string> nameOfColumn = {
        {name, "name"},
        {fullName, "full_name"},
        {phoneNumber, "phone_number"},
        {email, "email"},
        {title, "title"},
        {timeStart, "time_start"},
        {duration, "duration"},
        {clientId, "client_id"},
        {companyId, "company_id"},
        {employeeId, "employee_id"},
        {id, "id"},
        {all, "*"}
};

bool isIn(Column col, const std::vector<Column> &cols) {
    for(auto c: cols) {
        if(col == c) {
            return true;
        }
    }
    return false;
}
}

std::string Operation::execute() const {
    if (!canBeExecuted) {
        throw std::runtime_error("TODO");  // TODO
    }
    return s.str();
}

std::string Operation::parseCol(Column col) {
    if(col != all && !isIn(col, columnsOfTable[table])) {
        throw std::invalid_argument("TODO");  // TODO
    }
    return nameOfColumn[col];
}

Update::Update(Table t) {
    table = t;
    s << "UPDATE " << nameOfTable[table] << " SET ";
}

Update &Update::set(Column col, const std::string &value) {
    if (whereUsed) {
        throw std::invalid_argument("TODO");  // TODO
    }
    if (setUsed) {
        s << ", ";
    } else {
        setUsed = true;
    }
    if(isIn(col, stringColumns)) {
        s << parseCol(col) << " = '" << value << "' ";
    } else {
        s << parseCol(col) << " = " << value << " ";
    }
    canBeExecuted = true;
    return *this;
}

Update &Update::set(Column col, long long value) {
    if (!isIn(col, numericColumns)) {
        throw std::invalid_argument("TODO");  // TODO
    }
    if(value == -1) {
        return set(col, "NULL");
    }
    return set(col, std::to_string(value));
}

Update &Update::where(Column col, const std::string &value) {
    if (whereUsed) {
        s << "AND ";
    } else {
        whereUsed = true;
        s << "WHERE ";
    }
    if(value == "NULL" || value == "NOT NULL") {
        s << parseCol(col) << " IS " << value << " ";
    } else if(isIn(col, stringColumns)) {
        s << parseCol(col) << " = '" << value << "' ";
    } else {
        s << parseCol(col) << " = " << value << " ";
    }
    return *this;
}

Update &Update::where(Column col, long long value) {
    if (!isIn(col, numericColumns)) {
        throw std::invalid_argument("TODO");  // TODO
    }
    if(value == -1) {
        return where(col, "NULL");
    }
    return where(col, std::to_string(value));
}

Insert::Insert(Table t) {
    table = t;
    s << "INSERT INTO ";
    switch (table) {
        case clients:
            s << "clients(full_name, phone_number, email) ";
            requiredCols = {fullName, phoneNumber, email};
            break;
        case employees:
            s << "employees(company_id, full_name) ";
            requiredCols = {companyId, fullName};
            break;
        case orders:
            s << "orders(company_id, title, time_start, duration, employee_id) ";
            requiredCols = {companyId, title, timeStart, duration, employeeId};
            break;
        case companies:
            s << "companies(name) ";
            requiredCols = {name};
            break;
    }
    s << "VALUES (";
}

Insert &Insert::set(Column col, const std::string &value) {
    if (requiredCols.find(col) == requiredCols.end()) {
        throw std::invalid_argument("TODO");  // TODO
    }
    requiredCols.erase(col);
    if(isIn(col, stringColumns)) {
        currentValues[col] = "'" + value + "'";
    } else {
        currentValues[col] = value;
    }
    if (requiredCols.empty()) {
        switch (table) {
            case clients:
                s << currentValues[fullName] << ", "
                  << currentValues[phoneNumber] << ", " << currentValues[email];
                break;
            case employees:
                s << currentValues[companyId] << ", "
                  << currentValues[fullName];
                break;
            case orders:
                s << currentValues[companyId] << ", " << currentValues[title]
                  << ", " << currentValues[timeStart] << ", "
                  << currentValues[duration] << ", "
                  << currentValues[employeeId];
                break;
            case companies:
                s << currentValues[name];
                break;
        }
        s << ") RETURNING id";
        canBeExecuted = true;
    }
    return *this;
}

Insert &Insert::set(Column col, long long value) {
    if (!isIn(col, numericColumns)) {
        throw std::invalid_argument("TODO");  // TODO
    }
    if(value == -1) {
        return set(col, "NULL");
    }
    return set(col, std::to_string(value));
}

Select::Select(Table t) {
    table = t;
    s << "SELECT ";
}

Select &Select::columns(const std::vector<Column> &cols) {
    if (columnsUsed || whereUsed || orderedUsed) {
        throw std::invalid_argument("TODO");  // TODO
    }
    columnsUsed = true;
    bool first = true;
    for (auto col : cols) {
        if (!first) {
            s << ", ";
        } else {
            first = false;
        }
        s << parseCol(col);
    }
    s << " FROM " << nameOfTable[table] << " ";
    canBeExecuted = true;
    return *this;
}

Select &Select::where(Column col, const std::string &value) {
    if (whereUsed) {
        s << "AND ";
    } else {
        whereUsed = true;
        s << "WHERE ";
    }
    if(value == "NULL" || value == "NOT NULL") {
        s << parseCol(col) << " IS " << value << " ";
    } else if(isIn(col, stringColumns)) {
        s << parseCol(col) << " = '" << value << "' ";
    } else {
        s << parseCol(col) << " = " << value << " ";
    }
    return *this;
}

Select &Select::where(Column col, long long value) {
    if (!isIn(col, numericColumns)) {
        throw std::invalid_argument("TODO");  // TODO
    }
    if(value == -1) {
        return where(col, "NULL");
    }
    return where(col, std::to_string(value));
}

Select &Select::orderedBy(Column col) {
    if (orderedUsed) {
        throw std::invalid_argument("TODO");  // TODO
    }
    orderedUsed = true;
    s << "ORDERED BY " << parseCol(col);
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
    Employee employee(cur["id"].as<long long>(),
                      cur["company_id"].as<long long>(),
                      cur["full_name"].c_str());
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
    Order order(cur["id"].as<long long>(), cur["company_id"].as<long long>(),
                cur["title"].c_str(), cur["time_start"].c_str(),
                cur["duration"].c_str(), (cur["client_id"].is_null() ? -1 : cur["client_id"].as<long long>()),
                cur["employee_id"].as<long long>());
    return order;
}

Company Result::toCompany() {
    const pqxx::row &cur = res[0];
    Company company(cur["id"].as<long long>(), cur["name"].c_str());
    return company;
}

long long Result::toLL() {
    return res[0][0].as<long long>();
}

std::vector<long long> Result::toVecLL() {
    std::vector<long long> ans;
    for (auto && re : res) {
        ans.push_back(re["id"].as<long long>());
    }
    return ans;
}

Result Storage::execute(const Operation &op) {
    try {
        pqxx::work W{C};
        Result res(W.exec(op.execute()));
        W.commit();
        return res;
    } catch (const std::exception& e) {
        std::cerr << e.what();
        throw std::invalid_argument("TODO");  // TODO
    }
}

long long Storage::createCompany(const std::string &name_) {
    return execute(Insert(companies).set(name, name_)).toLL();
}

long long Storage::createOrder(long long companyId_,
                               const std::string &title_,
                               const std::string &timeStart_,
                               const std::string &duration_,
                               long long employeeId_) {
    return execute(Insert(orders)
                       .set(companyId, companyId_)
                       .set(title, title_)
                       .set(timeStart, timeStart_)
                       .set(duration, duration_)
                       .set(employeeId, employeeId_))
        .toLL();
}

long long Storage::createEmployee(long long companyId_,
                                  const std::string &fullName_) {
    return execute(Insert(employees)
                       .set(companyId, companyId_)
                       .set(fullName, fullName_))
        .toLL();
}

long long Storage::createClient(const std::string &fullName_,
                                const std::string &phoneNumber_,
                                const std::string &email_) {
    return execute(Insert(clients)
                       .set(fullName, fullName_)
                       .set(phoneNumber, phoneNumber_)
                       .set(email, email_))
        .toLL();
}

void Storage::storeEmployee(const Employee &employee) {
    execute(Update(employees)
                .set(fullName, employee.fullName)
                .where(id, employee.id));
}

void Storage::storeClient(const Client &client) {
    execute(Update(clients)
                .set(fullName, client.fullName)
                .set(phoneNumber, client.phoneNumber)
                .set(email, client.email)
                .where(id, client.id));
}

void Storage::storeOrder(const Order &order) {
    execute(Update(orders)
                .set(title, order.title)
                .set(timeStart, order.timeStart)
                .set(duration, order.duration)
                .set(clientId, order.clientId)
                .set(employeeId, order.employeeId)
                .where(id, order.id));
}

void Storage::storeCompany(const Company &company) {
    execute(Update(companies)
                .set(name, company.name)
                .where(id, company.id));
}

Employee Storage::getEmployeeById(long long id_) {
    return execute(Select(employees).columns({all}).where(id, id_))
        .toEmployee();
}

Client Storage::getClientById(long long id_) {
    return execute(Select(clients).columns({all}).where(id, id_)).toClient();
}

Order Storage::getOrderById(long long id_) {
    return execute(Select(orders).columns({all}).where(id, id_)).toOrder();
}

Company Storage::getCompanyById(long long id_) {
    return execute(Select(companies).columns({all}).where(id, id_)).toCompany();
}

void Storage::deleteEmployee(long long id) {
    // TODO
}

void Storage::deleteClient(long long id) {
    // TODO
}

void Storage::deleteOrder(long long id) {
    // TODO
}

void Storage::deleteCompany(long long id) {
    // TODO
}

std::vector<long long> Storage::listVacantOrdersOfCompany(long long id_) {
    auto a = Select(orders)
            .columns({id})
            .where(companyId, id_)
            .where(clientId, "NULL").execute();
    return execute(Select(orders)
                       .columns({id})
                       .where(companyId, id_)
                       .where(clientId, "NULL"))
        .toVecLL();
}

std::vector<long long> Storage::listBookedOrdersOfCompany(long long id_) {
    return execute(Select(orders)
                       .columns({id})
                       .where(companyId, id_)
                       .where(clientId, "NOT NULL"))
        .toVecLL();
}

std::vector<long long> Storage::listVacantOrdersOfEmployee(long long id_) {
    return execute(Select(orders)
                       .columns({id})
                       .where(employeeId, id_)
                       .where(clientId, "NULL"))
        .toVecLL();
}

std::vector<long long> Storage::listBookedOrdersOfEmployee(long long id_) {
    return execute(Select(orders)
                       .columns({id})
                       .where(employeeId, id_)
                       .where(clientId, "NOT NULL"))
        .toVecLL();
}

std::vector<long long> Storage::listOrdersOfClient(long long id_) {
    return execute(Select(orders).columns({id}).where(clientId, id_)).toVecLL();
}

std::vector<long long> Storage::listCompanies() {
    return execute(Select(companies).columns({id})).toVecLL();
}

std::vector<long long> Storage::listEmployeesOfCompany(long long id_) {
    return execute(Select(employees).columns({id}).where(companyId, id_))
        .toVecLL();
}

}  // namespace db