#ifndef BTIMETABLE_COMPANYAPI_H
#define BTIMETABLE_COMPANYAPI_H

#include "Entities.h"

namespace dataBase {
class CompanyAPI {
public:
    void createCompany(std::string name);

    Order createOrder(long long companyId,
                      std::string title,
                      int timeStart,
                      int duration,
                      int employeeId);

    Employee createEmployee(long long companyId, std::string fullName);

    std::vector<long long> listVacantOrders(long long companyId);

    std::vector<long long> listBookedOrders(long long companyId);

    std::vector<long long> listAllOrders(long long companyId);

    void deleteOrder(long long companyId, long long orderId);

    void deleteEmployee(long long companyId, long long employeeId);

    Order getOrderById(long long id);

    Employee getEmployeeById(long long id);

    Company getCompanyById(long long id);

    void modifyOrder(const Order &order);

    void modifyEmployee(const Employee &employee);

    std::vector<long long> listOrdersOfEmployee(long long id);
};
}

#endif //BTIMETABLE_COMPANYAPI_H
