#ifndef BTIMETABLE_COMPANYAPI_H
#define BTIMETABLE_COMPANYAPI_H

#include "Entities.h"

namespace dataBase {
class CompanyAPI {
public:
    static Company createCompany(std::string name);

    static Order createOrder(long long companyId,
                             std::string title,
                             int timeStart,
                             int duration,
                             int employeeId);

    static Employee createEmployee(long long companyId, std::string fullName);

    static std::vector<long long> listVacantOrdersOfCompany(long long id);

    static std::vector<long long> listBookedOrdersOfCompany(long long id);

    static std::vector<long long> listAllOrdersOfCompany(long long id);

    static Order getOrderById(long long id);

    static Employee getEmployeeById(long long id);

    static Company getCompanyById(long long id);

    static void changeOrderTitle(long long id, std::string title);

    static void changeOrderTimeStart(long long id, int timeStart);

    static void changeOrderDuration(long long id, int duration);

    static void changeEmployeeFullName(long long id, std::string fullName);

    static std::vector<long long> listVacantOrdersOfEmployee(long long id);

    static std::vector<long long> listBookedOrdersOfEmployee(long long id);

    static std::vector<long long> listAllOrdersOfEmployee(long long id);

    static std::vector<long long> listEmployeesOfCompany(long long id);
};
}  // namespace dataBase

#endif  // BTIMETABLE_COMPANYAPI_H
