#ifndef BTIMETABLE_COMPANYAPI_H
#define BTIMETABLE_COMPANYAPI_H

#include "Entities.h"

namespace db {
class CompanyAPI {
public:
    static long long createCompany(const std::string &phoneNumber,
                                   const std::string &password,
                                   const std::string &name);

    static long long authorizeCompany(const std::string &phoneNumber,
                                      const std::string &password);

    static long long createOrder(long long companyId,
                                 const std::string &title,
                                 long long timeStart,
                                 long long duration,
                                 long long employeeId);

    static long long createEmployee(long long companyId,
                                    const std::string &fullName);

    static std::vector<long long> listVacantOrdersOfCompany(long long id);

    static std::vector<long long> listBookedOrdersOfCompany(long long id);

    static std::vector<long long> listAllOrdersOfCompany(long long id);

    static Order getOrderById(long long id);

    static Employee getEmployeeById(long long id);

    static Company getCompanyById(long long id);

    static void changeOrderTitle(long long id, std::string title);

    static void changeOrderTimeStart(long long id, long long timeStart);

    static void changeOrderDuration(long long id, long long duration);

    static void changeEmployeeFullName(long long id, std::string fullName);

    static void deleteOrder(long long id);

    static std::vector<long long> listVacantOrdersOfEmployee(long long id);

    static std::vector<long long> listBookedOrdersOfEmployee(long long id);

    static std::vector<long long> listAllOrdersOfEmployee(long long id);

    static std::vector<long long> listEmployeesOfCompany(long long id);
};
}  // namespace db

#endif  // BTIMETABLE_COMPANYAPI_H
