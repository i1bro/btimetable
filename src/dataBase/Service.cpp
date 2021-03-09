
#include "Service.h"

namespace dataBase {

void Service::createCompany(std::string name) {
    Company company(std::move(name));
    storage.storeCompany(company);
}

Order Service::createOrder(std::string companyName,
                           std::string title,
                           int timeStart,
                           int duration,
                           int employeeId) {
    Order order(storage.giveOrderId(), std::move(title), timeStart, duration,
                employeeId);
    storage.setOrdersCompany(order.id, companyName);
    storage.addOrderToEmployee(employeeId, order.id);
    auto company = storage.getCompanyByName(std::move(companyName));
    company.addVacantOrder(order.id);
    storage.storeCompany(company);
    storage.storeOrder(order);
    return std::move(order);
}

Order Service::createOrder(std::string companyName,
                           std::string title,
                           int timeStart,
                           int duration,
                           int clientId,
                           int employeeId) {
    Order order(storage.giveOrderId(), std::move(title), timeStart, duration,
                clientId, employeeId);
    storage.setOrdersCompany(order.id, companyName);
    storage.addOrderToEmployee(employeeId, order.id);
    storage.addOrderToClient(clientId, order.id);
    auto company = storage.getCompanyByName(std::move(companyName));
    company.addBookedOrder(order.id);
    storage.storeCompany(company);
    storage.storeOrder(order);
    return std::move(order);
}

Employee Service::createEmployee(std::string companyName,
                                 std::string fullName) {
    Employee employee(storage.giveEmployeeId(), std::move(fullName));
    storage.setEmployeesCompany(employee.id, companyName);
    auto company = storage.getCompanyByName(std::move(companyName));
    company.addEmployee(employee.id);
    storage.storeCompany(company);
    storage.storeEmployee(employee);
    return std::move(employee);
}

Client Service::createClient(std::string fullName) {
    Client client(storage.giveClientId(), std::move(fullName));
    storage.storeClient(client);
    return std::move(client);
}

std::vector<long long> Service::listVacantOrders(std::string companyName) {
    auto company = storage.getCompanyByName(std::move(companyName));
    return company.listVacantOrders();
}

std::vector<long long> Service::listBookedOrders(std::string companyName) {
    auto company = storage.getCompanyByName(std::move(companyName));
    return company.listBookedOrders();
}

std::vector<long long> Service::listAllOrders(std::string companyName) {
    auto company = storage.getCompanyByName(std::move(companyName));
    auto response = company.listVacantOrders();
    for (auto i : company.listBookedOrders()) {
        response.push_back(i);
    }
    return std::move(response);
}

void Service::deleteOrder(std::string companyName, long long orderId) {
    auto company = storage.getCompanyByName(std::move(companyName));
    company.deleteOrder(orderId);
    storage.storeCompany(company);
}

void Service::deleteEmployee(std::string companyName, long long employeeId) {
    auto company = storage.getCompanyByName(std::move(companyName));
    company.deleteEmployee(employeeId);
    storage.storeCompany(company);
}

Order Service::getOrderById(long long int id) {
    return std::move(storage.getOrderById(id));
}

Employee Service::getEmployeeById(long long int id) {
    return std::move(storage.getEmployeeById(id));
}

Client Service::getClientById(long long int id) {
    return std::move(storage.getClientById(id));
}

void Service::modifyOrder(const Order &order) {
    auto oldOrder = storage.getOrderById(order.id);
    auto company = storage.getCompanyByName(storage.getOrdersCompany(order.id));
    company.deleteOrder(order.id);
    if (oldOrder.clientId != -1) {
        storage.deleteOrderOfClient(oldOrder.clientId, order.id);
    }
    storage.deleteOrderOfEmployee(oldOrder.employeeId, order.id);
    if (order.clientId != -1) {
        storage.addOrderToClient(order.clientId, order.id);
        company.addBookedOrder(order.id);
    } else {
        company.addVacantOrder(order.id);
    }
    storage.addOrderToEmployee(order.employeeId, order.id);
    storage.storeCompany(company);
    storage.storeOrder(order);
}

void Service::modifyEmployee(const Employee &employee) {
    storage.storeEmployee(employee);
}

void Service::modifyClient(const Client &client) {
    storage.storeClient(client);
}

std::vector<long long> Service::listOrdersOfEmployee(long long int employeeId) {
    return std::move(storage.listOrdersOfEmployee(employeeId));
}

std::vector<long long> Service::listOrdersOfClient(long long int clientId) {
    return std::move(storage.listOrdersOfClient(clientId));
}
}  // namespace dataBase
