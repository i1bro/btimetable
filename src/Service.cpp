
#include "btt/Service.h"

namespace db {

Company Service::createCompany(const std::string &phoneNumber,
                               const std::string &password,
                               const std::string &name) {
    long long resId =
        storage.execute(Insert(companies).set(Column::name, name)).toLL();
    storage.execute(Insert(companyAccounts)
                        .set(Column::phoneNumber, phoneNumber)
                        .set(Column::password, password)
                        .set(Column::companyId, resId));
    return getCompanyById(resId);
}

Order Service::createOrder(long long companyId,
                           const std::string &title,
                           const std::string &timeStart,
                           const std::string &duration,
                           long long employeeId) {
    long long resId = storage
                          .execute(Insert(orders)
                                       .set(Column::companyId, companyId)
                                       .set(Column::title, title)
                                       .set(Column::timeStart, timeStart)
                                       .set(Column::duration, duration)
                                       .set(Column::employeeId, employeeId))
                          .toLL();
    return getOrderById(resId);
}

Employee Service::createEmployee(long long companyId,
                                 const std::string &fullName) {
    long long resId = storage
                          .execute(Insert(employees)
                                       .set(Column::companyId, companyId)
                                       .set(Column::fullName, fullName))
                          .toLL();
    return getEmployeeById(resId);
}

Client Service::createClient(const std::string &phoneNumber,
                             const std::string &password,
                             const std::string &fullName,
                             const std::string &email) {
    long long resId = storage
                          .execute(Insert(clients)
                                       .set(Column::fullName, fullName)
                                       .set(Column::phoneNumber, phoneNumber)
                                       .set(Column::email, email))
                          .toLL();
    storage.execute(Insert(clientAccounts)
                        .set(Column::phoneNumber, phoneNumber)
                        .set(Column::password, password)
                        .set(Column::clientId, resId));
    return getClientById(resId);
}

std::vector<long long> Service::listVacantOrdersOfCompany(long long id) {
    return storage
        .execute(Select(orders)
                     .columns({Column::id})
                     .where(companyId, id)
                     .where(isDeleted, "FALSE")
                     .where(clientId, -1))
        .toVecLL();
}

std::vector<long long> Service::listBookedOrdersOfCompany(long long id) {
    return storage
        .execute(Select(orders)
                     .columns({Column::id})
                     .where(companyId, id)
                     .where(isDeleted, "FALSE")
                     .where(clientId, "NOT NULL"))
        .toVecLL();
}

std::vector<long long> Service::listAllOrdersOfCompany(long long id) {
    return storage
        .execute(Select(orders)
                     .columns({Column::id})
                     .where(companyId, id)
                     .where(isDeleted, "FALSE"))
        .toVecLL();
}

Order Service::getOrderById(long long id) {
    return storage.execute(Select(orders).columns({all}).where(Column::id, id))
        .toOrder();
}

Employee Service::getEmployeeById(long long id) {
    return storage
        .execute(Select(employees).columns({all}).where(Column::id, id))
        .toEmployee();
}

Client Service::getClientById(long long id) {
    return storage.execute(Select(clients).columns({all}).where(Column::id, id))
        .toClient();
}

Company Service::getCompanyById(long long id) {
    return storage
        .execute(Select(companies).columns({all}).where(Column::id, id))
        .toCompany();
}

void Service::saveOrder(const Order &order) {
    storage.execute(Update(orders)
                        .set(title, order.title)
                        .set(timeStart, order.timeStart)
                        .set(duration, order.duration)
                        .set(clientId, order.clientId)
                        .set(employeeId, order.employeeId)
                        .where(id, order.id));
}

void Service::saveEmployee(const Employee &employee) {
    storage.execute(Update(employees)
                        .set(fullName, employee.fullName)
                        .where(id, employee.id));
}

void Service::saveClient(const Client &client) {
    storage.execute(Update(clients)
                        .set(fullName, client.fullName)
                        .set(phoneNumber, client.phoneNumber)
                        .set(email, client.email)
                        .where(id, client.id));
}

void Service::saveCompany(const Company &company) {
    storage.execute(
        Update(companies).set(name, company.name).where(id, company.id));
}

std::vector<long long> Service::listVacantOrdersOfEmployee(long long id) {
    return storage
        .execute(Select(orders)
                     .columns({Column::id})
                     .where(employeeId, id)
                     .where(clientId, -1)
                     .where(isDeleted, "FALSE"))
        .toVecLL();
}

std::vector<long long> Service::listBookedOrdersOfEmployee(long long id) {
    return storage
        .execute(Select(orders)
                     .columns({Column::id})
                     .where(employeeId, id)
                     .where(clientId, "NOT NULL")
                     .where(isDeleted, "FALSE"))
        .toVecLL();
}

std::vector<long long> Service::listAllOrdersOfEmployee(long long id) {
    return storage
        .execute(Select(orders)
                     .columns({Column::id})
                     .where(employeeId, id)
                     .where(isDeleted, "FALSE"))
        .toVecLL();
}

std::vector<long long> Service::listOrdersOfClient(long long id) {
    return storage
        .execute(Select(orders)
                     .columns({Column::id})
                     .where(clientId, id)
                     .where(isDeleted, "FALSE"))
        .toVecLL();
}

std::vector<long long> Service::listCompanies() {
    return storage.execute(Select(companies).columns({id})).toVecLL();
}

std::vector<long long> Service::listEmployeesOfCompany(long long id) {
    return storage
        .execute(Select(employees).columns({Column::id}).where(companyId, id))
        .toVecLL();
}

void Service::deleteOrder(long long id) {
    storage.execute(
        Update(orders).set(isDeleted, "TRUE").where(Column::id, id));
}

long long Service::authorizeClient(const std::string &phoneNumber,
                                   const std::string &password) {
    auto res = storage.execute(Select(clientAccounts)
                                   .columns({clientId})
                                   .where(Column::phoneNumber, phoneNumber)
                                   .where(Column::password, password));
    try {
        return res.toLL();
    } catch (...) {
        return -1;
    }
}

long long Service::authorizeCompany(const std::string &phoneNumber,
                                    const std::string &password) {
    auto res = storage.execute(Select(companyAccounts)
                                   .columns({companyId})
                                   .where(Column::phoneNumber, phoneNumber)
                                   .where(Column::password, password));
    try {
        return res.toLL();
    } catch (...) {
        return -1;
    }
}
}  // namespace db
