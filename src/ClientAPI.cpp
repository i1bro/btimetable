#include "ClientAPI.h"

#include <utility>
#include "btt/Service.h"

namespace dataBase {

    Client ClientAPI::createClient(std::string fullName, std::string phoneNumber, std::string email) {
        return Service::createClient(std::move(fullName), std::move(phoneNumber), std::move(email));
    }

    std::vector<long long> ClientAPI::listCompanies() {
        //TODO
        //return Service::listCompanies;
        return std::vector<long long> ();
    }

    std::vector<long long> ClientAPI::listVacantOrdersOfCompany(long long id) {
        return Service::listVacantOrdersOfCompany(id);
    }

    std::vector<long long> ClientAPI::listEmployeesOfCompany(long long id) {
        //TODO
        //return Service::listEmployeesOfCompany(id);
        return std::vector<long long> ();
    }

    void ClientAPI::bookOrder(long long orderId, long long clientId) {
        auto order = Service::getOrderById(orderId);
        order.clientId = clientId;
        Service::saveOrder(order);
    }

    void ClientAPI::cancelOrder(long long orderId) {
        auto order = Service::getOrderById(orderId);
        order.clientId = -1;
        Service::saveOrder(order);
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

}