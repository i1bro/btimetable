#ifndef BTIMETABLE_SERVICE_H
#define BTIMETABLE_SERVICE_H

#include "Entities.h"
#include "Storage.h"

namespace dataBase {

class Service {
private:
    Storage storage;

public:
    Service() = default;

    void createCompany(std::string name);

    Order createOrder(std::string companyName,
                      std::string title,
                      int timeStart,
                      int duration,
                      int employeeId);

    Order createOrder(std::string companyName,
                      std::string title,
                      int timeStart,
                      int duration,
                      int clientId,
                      int employeeId);

    Employee createEmployee(std::string companyName, std::string fullName);

    Client createClient(std::string fullName);

    std::vector<long long> listVacantOrders(std::string companyName);

    std::vector<long long> listBookedOrders(std::string companyName);

    std::vector<long long> listAllOrders(std::string companyName);

    void deleteOrder(std::string companyName, long long orderId);

    void deleteEmployee(std::string companyName, long long employeeId);

    Order getOrderById(long long id);

    Employee getEmployeeById(long long id);

    Client getClientById(long long id);

    void modifyOrder(const Order &order);

    void modifyEmployee(const Employee &employee);

    void modifyClient(const Client &client);

    std::vector<long long> listOrdersOfEmployee(long long employeeId);

    std::vector<long long> listOrdersOfClient(long long clientId);
};

}  // namespace dataBase

#endif  // BTIMETABLE_SERVICE_H
