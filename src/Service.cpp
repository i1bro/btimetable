
#include "btt/Service.h"

namespace dataBase {

Company Service::createCompany(std::string name) {
    Company company(storage.giveCompanyId(), std::move(name));
    storage.storeCompany(company);
    return std::move(company);
}

Order Service::createOrder(long long companyId,
                           std::string title,
                           int timeStart,
                           int duration,
                           int employeeId) {
    Order order(storage.giveOrderId(), companyId, std::move(title), timeStart,
                duration, employeeId);
    storage.storeOrder(order);
    return std::move(order);
}

Order Service::createOrder(long long companyId,
                           std::string title,
                           int timeStart,
                           int duration,
                           int clientId,
                           int employeeId) {
    Order order(storage.giveOrderId(), companyId, std::move(title), timeStart,
                duration, clientId, employeeId);
    storage.storeOrder(order);
    return std::move(order);
}

Employee Service::createEmployee(long long companyId, std::string fullName) {
    Employee employee(storage.giveEmployeeId(), companyId, std::move(fullName));
    storage.storeEmployee(employee);
    return std::move(employee);
}

Client Service::createClient(std::string fullName,
                             std::string phoneNumber,
                             std::string email) {
    Client client(storage.giveClientId(), std::move(fullName),
                  std::move(phoneNumber), std::move(email));
    storage.storeClient(client);
    return std::move(client);
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
    auto oldOrder = storage.getOrderById(order.id);
    if (oldOrder.clientId != -1) {
        storage.deleteOrderOfClient(oldOrder.clientId, order.id);
    }
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
}  // namespace dataBase
