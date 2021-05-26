#include "ClientAPI.h"
#include "btt/Service.h"

namespace db {

long long ClientAPI::createClient(const std::string &phoneNumber,
                                  const std::string &password,
                                  const std::string &fullName,
                                  const std::string &email) {
    return Service::createClient(phoneNumber, password, fullName, email);
}

std::vector<long long> ClientAPI::listCompanies() {
    return Service::listCompanies();
}

std::vector<long long> ClientAPI::listVacantOrdersOfCompany(long long id) {
    return Service::listVacantOrdersOfCompany(id);
}

std::vector<long long> ClientAPI::listEmployeesOfCompany(long long id) {
    return Service::listEmployeesOfCompany(id);
}

void ClientAPI::bookOrder(long long orderId, long long clientId) {
    Service::bookOrder(orderId, clientId);
}

void ClientAPI::cancelOrder(long long orderId) {
    Service::cancelOrder(orderId);
}

void ClientAPI::rateOrder(long long id, int rating) {
    Service::rateOrder(id, rating);
}

Client ClientAPI::getClientById(long long id) {
    return Service::getClientById(id);
}

Order ClientAPI::getOrderById(long long id) {
    return Service::getOrderById(id);
}

Employee ClientAPI::getEmployeeById(long long id) {
    return Service::getEmployeeById(id);
}

Company ClientAPI::getCompanyById(long long id) {
    return Service::getCompanyById(id);
}

void ClientAPI::changeClientFullName(long long id, std::string fullName) {
    auto client = Service::getClientById(id);
    client.fullName = std::move(fullName);
    Service::saveClient(client);
}

void ClientAPI::changeClientPhoneNumber(long long id, std::string phoneNumber) {
    auto client = Service::getClientById(id);
    client.phoneNumber = std::move(phoneNumber);
    Service::saveClient(client);
}

void ClientAPI::changeClientEmail(long long id, std::string email) {
    auto client = Service::getClientById(id);
    client.email = std::move(email);
    Service::saveClient(client);
}

std::vector<long long> ClientAPI::listOrdersOfClient(long long id) {
    return Service::listOrdersOfClient(id);
}

std::vector<long long> ClientAPI::listVacantOrdersOfEmployee(long long id) {
    return Service::listVacantOrdersOfEmployee(id);
}

long long ClientAPI::authorizeClient(const std::string &phoneNumber,
                                     const std::string &password) {
    return Service::authorizeClient(phoneNumber, password);
}

std::vector<long long> ClientAPI::listOrders(long long int companyId,
                                             long long int employeeId,
                                             Order::statusEnum status,
                                             long long int leastTimeStart,
                                             long long int leastDuration,
                                             sortParam sortBy,
                                             bool reversed) {
    return Service::listOrders(companyId, employeeId, status, leastTimeStart,
                               leastDuration, sortBy, reversed);
}

}  // namespace db