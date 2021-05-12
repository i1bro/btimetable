#include "btt/Storage.h"

namespace db {

std::string Operation::execute() const {
    if (!canBeExecuted) {
        throw std::runtime_error("TODO");  // TODO
    }
    return s.str();
}

std::string Operation::parseCol(column col) {
    if (col == id) {
        return "id";
    }
    if (col == all) {
        return "*";
    }
    switch (table) {
        case clients:
            switch (col) {
                case fullName:
                    return "full_name";
                case phoneNumber:
                    return "phone_number";
                case email:
                    return "email";
                default:
                    throw std::invalid_argument("TODO");  // TODO
            }
        case employees:
            switch (col) {
                case companyId:
                    return "company_id";
                case fullName:
                    return "full_name";
                default:
                    throw std::invalid_argument("TODO");  // TODO
            }
        case orders:
            switch (col) {
                case companyId:
                    return "company_id";
                case title:
                    return "title";
                case duration:
                    return "duration";
                case timeStart:
                    return "time_start";
                case clientId:
                    return "client_id";
                case employeeId:
                    return "employee_id";
                default:
                    throw std::invalid_argument("TODO");  // TODO
            }
        case companies:
            switch (col) {
                case name:
                    return "name";
                default:
                    throw std::invalid_argument("TODO");  // TODO
            }
    }
}

Update::Update(Tables t) {
    table = t;
    s << "UPDATE ";
    switch (table) {
        case clients:
            s << "clients ";
            break;
        case employees:
            s << "employees ";
            break;
        case orders:
            s << "orders ";
            break;
        case companies:
            s << "companies ";
            break;
    }
    s << "SET ";
}

Update &Update::set(column col, const std::string &value) {
    if (whereUsed) {
        throw std::invalid_argument("TODO");  // TODO
    }
    if (setUsed) {
        s << ", ";
    } else {
        setUsed = true;
    }
    s << parseCol(col) << " = " << value << " ";
    return *this;
}

Update &Update::set(column col, long long value) {
    canBeExecuted = true;
    if (col != clientId) {
        throw std::invalid_argument("TODO");  // TODO
    }
    return set(col, std::to_string(value));
}

Update &Update::where(column col, const std::string &value) {
    if (whereUsed) {
        s << "AND ";
    } else {
        whereUsed = true;
        s << "WHERE ";
    }
    s << parseCol(col) << " = " << value << " ";
    return *this;
}

Update &Update::where(column col, long long value) {
    if (col != clientId && col != id) {
        throw std::invalid_argument("TODO");  // TODO
    }
    return where(col, std::to_string(value));
}

Insert::Insert(Tables t) {
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
            s << "orders(company_id, title, time_start, duration, employeeId) ";
            requiredCols = {companyId, title, timeStart, duration, employeeId};
            break;
        case companies:
            s << "companies(name) ";
            requiredCols = {name};
            break;
    }
    s << "VALUES (";
}

Insert &Insert::set(column col, const std::string &value) {
    if (requiredCols.find(col) == requiredCols.end()) {
        throw std::invalid_argument("TODO");  // TODO
    }
    requiredCols.erase(col);
    currentValues[col] = value;
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

Insert &Insert::set(column col, long long value) {
    if (col != employeeId && col != companyId) {
        throw std::invalid_argument("TODO");  // TODO
    }
    return set(col, std::to_string(value));
}

Select::Select(Tables t) {
    table = t;
    s << "SELECT ";
}

Select &Select::columns(const std::vector<column> &cols) {
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
    s << " FROM ";
    switch (table) {
        case clients:
            s << "clients ";
            break;
        case employees:
            s << "employees ";
            break;
        case orders:
            s << "orders ";
            break;
        case companies:
            s << "companies ";
            break;
    }
    canBeExecuted = true;
    return *this;
}

Select &Select::where(column col, const std::string &value) {
    if (orderedUsed) {
        throw std::invalid_argument("TODO");  // TODO
    }
    if (whereUsed) {
        s << "AND ";
    } else {
        whereUsed = true;
        s << "WHERE ";
    }
    s << parseCol(col) << " = " << value << " ";
    return *this;
}

Select &Select::where(column col, long long value) {
    if (col != employeeId && col != companyId && col != clientId && col != id) {
        throw std::invalid_argument("TODO");  // TODO
    }
    return where(col, std::to_string(value));
}

Select &Select::orderedBy(column col) {
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
    pqxx::row cur = res[0];
    Employee employee(cur["id"].as<long long>(),
                      cur["company_id"].as<long long>(),
                      cur["full_name"].c_str());
    return employee;
}

Client Result::toClient() {
    pqxx::row cur = res[0];
    Client client(cur["id"].as<long long>(), cur["full_name"].c_str(),
                  cur["phone_number"].c_str(), cur["email"].c_str());
    return client;
}

Order Result::toOrder() {
    pqxx::row cur = res[0];
    Order order(cur["id"].as<long long>(), cur["company_id"].as<long long>(),
                cur["title"].c_str(), cur["timeStart"].c_str(),
                cur["duration"].c_str(), cur["client_id"].as<long long>(),
                cur["employee_id"].as<long long>());
    return order;
}

Company Result::toCompany() {
    pqxx::row cur = res[0];
    Company company(cur["id"].as<long long>(), cur["name"].c_str());
    return company;
}

long long Result::toLL() {
    pqxx::row cur = res[0];
    return cur[0].as<long long>();
}

std::vector<long long> Result::toVecLL() {
    std::vector<long long> ans;
    for (int i = 0; i < res.size(); i++) {
        ans.push_back(res[0]["id"].as<long long>());
    }
    return ans;
}

Result Storage::execute(const Operation &op) {
    try {
        pqxx::work W{C};
        Result res(W.exec(op.execute()));
        W.commit();
    } catch (...) {
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
    execute(Update(employees).set(fullName, employee.fullName));
}

void Storage::storeClient(const Client &client) {
    execute(Update(clients)
                .set(fullName, client.fullName)
                .set(phoneNumber, client.phoneNumber)
                .set(email, client.email));
}

void Storage::storeOrder(const Order &order) {
    execute(Update(orders)
                .set(title, order.title)
                .set(timeStart, order.timeStart)
                .set(duration, order.duration)
                .set(clientId, order.clientId)
                .set(employeeId, order.employeeId));
}

void Storage::storeCompany(const Company &company) {
    execute(Update(companies).set(name, company.name));
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