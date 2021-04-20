#ifndef BTIMETABLE_SERVICE_H
#define BTIMETABLE_SERVICE_H

#include "Entities.h"
#include "Storage.h"

namespace dataBase {

class Service {
private:
    Storage storage;

    void saveOrder(const Order &order);

    void saveEmployee(const Employee &employee);

    void saveClient(const Client &client);

    void saveCompany(const Company &company);

public:
    Service() = default;

    void createCompany(std::string name);

    Order createOrder(long long companyId,
                      std::string title,
                      int timeStart,
                      int duration,
                      int employeeId);

    Order createOrder(long long companyId,
                      std::string title,
                      int timeStart,
                      int duration,
                      int clientId,
                      int employeeId);

    Employee createEmployee(long long companyId, std::string fullName);

    Client createClient(std::string fullName, std::string phoneNumber, std::string email);

    std::vector<long long> listVacantOrders(long long companyId);

    std::vector<long long> listBookedOrders(long long companyId);

    std::vector<long long> listAllOrders(long long companyId);

    void deleteOrder(long long companyId, long long orderId);

    void deleteEmployee(long long companyId, long long employeeId);

    Order getOrderById(long long id);

    Employee getEmployeeById(long long id);

    Client getClientById(long long id);

    Company getCompanyById(long long id);

    std::vector<long long> listOrdersOfEmployee(long long employeeId);

    std::vector<long long> listOrdersOfClient(long long clientId);
};

}  // namespace dataBase

#endif  // BTIMETABLE_SERVICE_H
