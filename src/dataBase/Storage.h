#ifndef BTIMETABLE_STORAGE_H
#define BTIMETABLE_STORAGE_H

#include <sw/redis++/redis++.h>
#include "Entities.h"

namespace dataBase {

class Storage {
private:
    sw::redis::Redis redis = sw::redis::Redis("tcp://127.0.0.1:6379");

    void storeSchedule(const Schedule &schedule, std::string &&prefix = "");
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

    void setEmployeesCompany(long long employeeId, long long companyId);

    void setOrdersCompany(long long orderId, long long companyId);

    long long getEmployeesCompany(long long employeeId);

    long long getOrdersCompany(long long orderId);

    void addOrderToEmployee(long long employeeId, long long orderId);

    void addOrderToClient(long long clientId, long long orderId);

    void deleteOrderOfEmployee(long long employeeId, long long orderId);

    void deleteOrderOfClient(long long clientId, long long orderId);

    std::vector<long long> listOrdersOfEmployee(long long employeeId);

    std::vector<long long> listOrdersOfClient(long long clientId);
};

}  // namespace dataBase

#endif  // BTIMETABLE_STORAGE_H
