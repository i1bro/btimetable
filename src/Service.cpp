
#include "btt/Service.h"

namespace db {

Company Service::createCompany(const std::string &name) {
    long long res = storage.createCompany(name);
    return storage.getCompanyById(res);
}

Order Service::createOrder(long long companyId,
                           const std::string &title,
                           const std::string &timeStart,
                           const std::string &duration,
                           long long employeeId) {
    long long res =
        storage.createOrder(companyId, title, timeStart, duration, employeeId);
    return storage.getOrderById(res);
}

Employee Service::createEmployee(long long companyId,
                                 const std::string &fullName) {
    long long res = storage.createEmployee(companyId, fullName);
    return storage.getEmployeeById(res);
}

Client Service::createClient(const std::string &fullName,
                             const std::string &phoneNumber,
                             const std::string &email) {
    long long res = storage.createClient(fullName, phoneNumber, email);
    return storage.getClientById(res);
}

std::vector<long long> Service::listVacantOrdersOfCompany(long long id) {
    return std::move(storage.listVacantOrdersOfCompany(id));
}

std::vector<long long> Service::listBookedOrdersOfCompany(long long id) {
    return std::move(storage.listBookedOrdersOfCompany(id));
}

std::vector<long long> Service::listAllOrdersOfCompany(long long id) {
    auto response = storage.listVacantOrdersOfCompany(id);
    for (auto i : storage.listBookedOrdersOfCompany(id)) {
        response.push_back(i);
    }
    return std::move(response);
}

Order Service::getOrderById(long long id) {
    return std::move(storage.getOrderById(id));
}

Employee Service::getEmployeeById(long long id) {
    return std::move(storage.getEmployeeById(id));
}

Client Service::getClientById(long long id) {
    return std::move(storage.getClientById(id));
}

Company Service::getCompanyById(long long id) {
    return std::move(storage.getCompanyById(id));
}

void Service::saveOrder(const Order &order) {
    storage.storeOrder(order);
}

void Service::saveEmployee(const Employee &employee) {
    storage.storeEmployee(employee);
}

void Service::saveClient(const Client &client) {
    storage.storeClient(client);
}

void Service::saveCompany(const Company &company) {
    storage.storeCompany(company);
}

std::vector<long long> Service::listVacantOrdersOfEmployee(long long id) {
    return std::move(storage.listVacantOrdersOfEmployee(id));
}

std::vector<long long> Service::listBookedOrdersOfEmployee(long long id) {
    return std::move(storage.listBookedOrdersOfEmployee(id));
}

std::vector<long long> Service::listAllOrdersOfEmployee(long long id) {
    auto response = storage.listVacantOrdersOfEmployee(id);
    for (auto i : storage.listBookedOrdersOfEmployee(id)) {
        response.push_back(i);
    }
    return std::move(response);
}

std::vector<long long> Service::listOrdersOfClient(long long id) {
    return std::move(storage.listOrdersOfClient(id));
}

std::vector<long long> Service::listCompanies() {
    return storage.listCompanies();
}

std::vector<long long> Service::listEmployeesOfCompany(long long id) {
    return storage.listEmployeesOfCompany(id);
}
}  // namespace db
