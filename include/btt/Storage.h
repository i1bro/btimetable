#ifndef BTIMETABLE_STORAGE_H
#define BTIMETABLE_STORAGE_H

#include <sw/redis++/redis++.h>
#include "Entities.h"

namespace dataBase {

class Storage {
private:
    sw::redis::Redis redis = sw::redis::Redis("tcp://retired.tk:58973");

public:
    Storage() = default;

    long long giveEmployeeId();

    long long giveClientId();

    long long giveOrderId();

    long long giveCompanyId();

    void storeEmployee(const Employee &employee);

    void storeClient(const Client &client);

    void storeOrder(const Order &order);

    void storeCompany(const Company &company);

    Employee getEmployeeById(long long id);

    Client getClientById(long long id);

    Order getOrderById(long long id);

    Company getCompanyById(long long id);

    void deleteEmployee(long long id);

    void deleteClient(long long id);

    void deleteOrder(long long id);

    void deleteCompany(long long id);

    long long getEmployeeOwner(long long employeeId);

    long long getOrderOwner(long long orderId);

    void deleteOrderOfClient(long long clientId, long long orderId);

    std::vector<long long> listVacantOrdersOfCompany(long long employeeId);

    std::vector<long long> listBookedOrdersOfCompany(long long employeeId);

    std::vector<long long> listVacantOrdersOfEmployee(long long employeeId);

    std::vector<long long> listBookedOrdersOfEmployee(long long employeeId);

    std::vector<long long> listOrdersOfClient(long long clientId);

    std::vector<long long> listCompanies();

    std::vector<long long> listEmployeesOfCompany(long long id);
};

}  // namespace dataBase

#endif  // BTIMETABLE_STORAGE_H
