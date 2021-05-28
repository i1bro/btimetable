#ifndef BTIMETABLE_SERVICE_H
#define BTIMETABLE_SERVICE_H

#include <string>
#include <vector>
#include "Entities.h"
#include "Storage.h"

namespace db {

class Service {
private:
    static Storage &storage();

public:
    Service() = default;

    static long long createCompany(const std::string &phoneNumber,
                                   const std::string &password,
                                   const std::string &name);

    static long long createOrder(long long companyId,
                                 const std::string &title,
                                 long long timeStart,
                                 long long duration,
                                 long long employeeId);

    static long long createEmployee(long long companyId,
                                    const std::string &fullName);

    static long long createClient(const std::string &phoneNumber,
                                  const std::string &password,
                                  const std::string &fullName,
                                  const std::string &email);

    static long long authorizeClient(const std::string &phoneNumber,
                                     const std::string &password);

    static long long authorizeCompany(const std::string &phoneNumber,
                                      const std::string &password);

    static std::vector<long long> listOrders(const orderSearchParams &params);

    static std::vector<long long> listVacantOrdersOfCompany(long long id);

    static std::vector<long long> listBookedOrdersOfCompany(long long id);

    static std::vector<long long> listAllOrdersOfCompany(long long id);

    static void saveOrder(const Order &order);

    static void saveEmployee(const Employee &employee);

    static void saveClient(const Client &client);

    static void saveCompany(const Company &company);

    static Order getOrderById(long long id);

    static Employee getEmployeeById(long long id);

    static Client getClientById(long long id);

    static Company getCompanyById(long long id);

    static void deleteEmployee(long long id);

    static void deleteOrder(long long id);

    static void bookOrder(long long orderId, long long clientId);

    static void cancelOrder(long long id);

    static void rateOrder(long long id, int rating);

    static std::vector<long long> listVacantOrdersOfEmployee(long long id);

    static std::vector<long long> listBookedOrdersOfEmployee(long long id);

    static std::vector<long long> listAllOrdersOfEmployee(long long id);

    static std::vector<long long> listOrdersOfClient(long long id);

    static std::vector<long long> listCompanies(sortParam sorted = byRating);

    static std::vector<long long> listEmployeesOfCompany(
        long long id,
        sortParam sorted = byRating);

    static std::string createToken(long long id, const std::string &role);

    static long long verifyToken(const std::string &token,
                                 const std::string &role);
};

}  // namespace db

#endif  // BTIMETABLE_SERVICE_H
