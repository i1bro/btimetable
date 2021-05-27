#ifndef BTIMETABLE_COMPANYAPI_H
#define BTIMETABLE_COMPANYAPI_H

#include "Entities.h"

namespace db {
class CompanyAPI {
public:
    static std::string createCompany(const std::string &phoneNumber,
                                     const std::string &password,
                                     const std::string &name);

    static std::string authorizeCompany(const std::string &phoneNumber,
                                        const std::string &password);

    static long long createOrder(const std::string &token,
                                 const std::string &title,
                                 long long timeStart,
                                 long long duration,
                                 long long employeeId);

    static long long createEmployee(const std::string &token,
                                    const std::string &fullName);

    static std::vector<long long> listVacantOrdersOfCompany(
        const std::string &token);

    static std::vector<long long> listBookedOrdersOfCompany(
        const std::string &token);

    static std::vector<long long> listAllOrdersOfCompany(
        const std::string &token);

    static Order getOrderById(const std::string &token, long long orderId);

    static Employee getEmployeeById(const std::string &token,
                                    long long employeeId);

    static Company getCompany(const std::string &token);

    static void changeOrderTitle(const std::string &token,
                                 long long orderId,
                                 std::string title);

    static void changeOrderTimeStart(const std::string &token,
                                     long long orderId,
                                     long long timeStart);

    static void changeOrderDuration(const std::string &token,
                                    long long orderId,
                                    long long duration);

    static void changeEmployeeFullName(const std::string &token,
                                       long long employeeId,
                                       std::string fullName);

    static void deleteEmployee(const std::string &token, long long employeeId);

    static void deleteOrder(const std::string &token, long long orderId);

    static std::vector<long long> listVacantOrdersOfEmployee(
        const std::string &token,
        long long employeeId);

    static std::vector<long long> listBookedOrdersOfEmployee(
        const std::string &token,
        long long employeeId);

    static std::vector<long long> listAllOrdersOfEmployee(
        const std::string &token,
        long long employeeId);

    static std::vector<long long> listEmployeesOfCompany(
        const std::string &token, sortParam sorted = byRating);
};
}  // namespace db

#endif  // BTIMETABLE_COMPANYAPI_H
