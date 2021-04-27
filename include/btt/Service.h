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

    Company createCompany(std::string name);

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

    std::vector<long long> listVacantOrdersOfCompany(long long id);

    std::vector<long long> listBookedOrdersOfCompany(long long id);

    std::vector<long long> listAllOrdersOfCompany(long long id);

    void saveOrder(const Order &order);

    void saveEmployee(const Employee &employee);

    void saveClient(const Client &client);

    void saveCompany(const Company &company);

    Order getOrderById(long long id);

    Employee getEmployeeById(long long id);

    Client getClientById(long long id);

    Company getCompanyById(long long id);

    //void deleteOrder(long long Id);

    //void deleteEmployee(long long Id);

    std::vector<long long> listVacantOrdersOfEmployee(long long id);

    std::vector<long long> listBookedOrdersOfEmployee(long long id);

    std::vector<long long> listAllOrdersOfEmployee(long long id);

    std::vector<long long> listOrdersOfClient(long long id);
};

}  // namespace dataBase

#endif  // BTIMETABLE_SERVICE_H
