#include "ClientAPI.h"
#include "btt/Service.h"

namespace db {

namespace {
const std::string role = "client";

struct bttClientPermissionError : bttError {
    explicit bttClientPermissionError()
        : bttError(
              "You don't have access to this order: it is deleted or booked by "
              "someone else.") {
    }
};
}  // namespace

std::string ClientAPI::createClient(const std::string &phoneNumber,
                                    const std::string &password,
                                    const std::string &fullName,
                                    const std::string &email) {
    return Service::createToken(
        Service::createClient(phoneNumber, password, fullName, email), role);
}

std::vector<long long> ClientAPI::listCompanies(sortParam sorted) {
    return Service::listCompanies(sorted);
}

std::vector<long long> ClientAPI::listVacantOrdersOfCompany(
    long long companyId) {
    return Service::listVacantOrdersOfCompany(companyId);
}

std::vector<long long> ClientAPI::listEmployeesOfCompany(long long companyId,
                                                         sortParam sorted) {
    return Service::listEmployeesOfCompany(companyId, sorted);
}

void ClientAPI::bookOrder(const std::string &token, long long orderId) {
    auto parsed = Service::verifyToken(token, role);
    auto order = Service::getOrderById(orderId);
    if (order.status != Order::vacant) {
        throw bttClientPermissionError();
    }
    Service::bookOrder(orderId, parsed);
}

void ClientAPI::cancelOrder(const std::string &token, long long orderId) {
    auto parsed = Service::verifyToken(token, role);
    auto order = Service::getOrderById(orderId);
    if (order.status != Order::booked || order.clientId != parsed) {
        throw bttClientPermissionError();
    }
    Service::cancelOrder(orderId);
}

void ClientAPI::rateOrder(const std::string &token,
                          long long orderId,
                          int rating) {
    auto parsed = Service::verifyToken(token, role);
    auto order = Service::getOrderById(orderId);
    if (order.status != Order::booked || order.clientId != parsed) {
        throw bttClientPermissionError();
    }
    Service::rateOrder(orderId, rating);
}

Client ClientAPI::getClient(const std::string &token) {
    auto parsed = Service::verifyToken(token, role);
    return Service::getClientById(parsed);
}

Order ClientAPI::getOrderById(const std::string &token, long long orderId) {
    auto parsed = Service::verifyToken(token, role);
    auto order = Service::getOrderById(orderId);
    if (order.status != Order::vacant && order.clientId != parsed) {
        throw bttClientPermissionError();
    }
    return Service::getOrderById(orderId);
}

Employee ClientAPI::getEmployeeById(long long employeeId) {
    return Service::getEmployeeById(employeeId);
}

Company ClientAPI::getCompanyById(long long companyId) {
    return Service::getCompanyById(companyId);
}

void ClientAPI::changeClientFullName(const std::string &token,
                                     std::string fullName) {
    auto parsed = Service::verifyToken(token, role);
    auto client = Service::getClientById(parsed);
    client.fullName = std::move(fullName);
    Service::saveClient(client);
}

void ClientAPI::changeClientEmail(const std::string &token, std::string email) {
    auto parsed = Service::verifyToken(token, role);
    auto client = Service::getClientById(parsed);
    client.email = std::move(email);
    Service::saveClient(client);
}

std::vector<long long> ClientAPI::listOrdersOfClient(const std::string &token) {
    auto parsed = Service::verifyToken(token, role);
    return Service::listOrdersOfClient(parsed);
}

std::vector<long long> ClientAPI::listVacantOrdersOfEmployee(
    long long employeeId) {
    return Service::listVacantOrdersOfEmployee(employeeId);
}

std::string ClientAPI::authorizeClient(const std::string &phoneNumber,
                                       const std::string &password) {
    return Service::createToken(Service::authorizeClient(phoneNumber, password),
                                role);
}

std::vector<long long> ClientAPI::listOrders(const orderSearchParams &params) {
    return Service::listOrders(params);
}

}  // namespace db