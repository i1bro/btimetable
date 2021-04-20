
#include "Service.h"

namespace dataBase {

void Service::createCompany(std::string name) {
    Company company(storage.giveCompanyId(), std::move(name));
    storage.storeCompany(company);
}

Order Service::createOrder(long long companyId,
                           std::string title,
                           int timeStart,
                           int duration,
                           int employeeId) {
    Order order(storage.giveOrderId(), std::move(title), timeStart, duration,
                employeeId);
    storage.setOrdersCompany(order.id, companyId);
    storage.addOrderToEmployee(employeeId, order.id);
    auto company = storage.getCompanyById(companyId);
    company.addVacantOrder(order.id);
    storage.storeCompany(company);
    storage.storeOrder(order);
    return std::move(order);
}

Order Service::createOrder(long long companyId,
                           std::string title,
                           int timeStart,
                           int duration,
                           int clientId,
                           int employeeId) {
    Order order(storage.giveOrderId(), std::move(title), timeStart, duration,
                clientId, employeeId);
    storage.setOrdersCompany(order.id, companyId);
    storage.addOrderToEmployee(employeeId, order.id);
    storage.addOrderToClient(clientId, order.id);
    auto company = storage.getCompanyById(companyId);
    company.addBookedOrder(order.id);
    storage.storeCompany(company);
    storage.storeOrder(order);
    return std::move(order);
}

Employee Service::createEmployee(long long companyId,
                                 std::string fullName) {
    Employee employee(storage.giveEmployeeId(), std::move(fullName));
    storage.setEmployeesCompany(employee.id, companyId);
    auto company = storage.getCompanyById(companyId);
    company.addEmployee(employee.id);
    storage.storeCompany(company);
    storage.storeEmployee(employee);
    return std::move(employee);
}

Client Service::createClient(std::string fullName, std::string phoneNumber, std::string email) {
    Client client(storage.giveClientId(), std::move(fullName), std::move(phoneNumber), std::move(email));
    storage.storeClient(client);
    return std::move(client);
}

std::vector<long long> Service::listVacantOrders(long long companyId) {
    auto company = storage.getCompanyById(companyId);
    return company.listVacantOrders();
}

std::vector<long long> Service::listBookedOrders(long long companyId) {
    auto company = storage.getCompanyById(companyId);
    return company.listBookedOrders();
}

std::vector<long long> Service::listAllOrders(long long companyId) {
    auto company = storage.getCompanyById(companyId);
    auto response = company.listVacantOrders();
    for (auto i : company.listBookedOrders()) {
        response.push_back(i);
    }
    return std::move(response);
}

void Service::deleteOrder(long long companyId, long long orderId) {
    auto company = storage.getCompanyById(companyId);
    company.deleteOrder(orderId);
    storage.storeCompany(company);
}

void Service::deleteEmployee(long long companyId, long long employeeId) {
    auto company = storage.getCompanyById(companyId);
    company.deleteEmployee(employeeId);
    storage.storeCompany(company);
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
    auto company = storage.getCompanyById(storage.getOrdersCompany(order.id));
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

void Service::saveEmployee(const Employee &employee) {
    storage.storeEmployee(employee);
}

void Service::saveClient(const Client &client) {
    storage.storeClient(client);
}

void Service::saveCompany(const Company &company) {
    storage.storeCompany(company);
}

std::vector<long long> Service::listOrdersOfEmployee(long long int employeeId) {
    return std::move(storage.listOrdersOfEmployee(employeeId));
}

std::vector<long long> Service::listOrdersOfClient(long long int clientId) {
    return std::move(storage.listOrdersOfClient(clientId));
}
}  // namespace dataBase
