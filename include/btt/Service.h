#ifndef BTIMETABLE_SERVICE_H
#define BTIMETABLE_SERVICE_H

#include "Entities.h"
#include "Storage.h"

namespace db {

class Service {
private:
    inline static Storage storage = Storage();

public:
    Service() = default;

    static Company createCompany(const std::string &phoneNumber,
                                 const std::string &password,
                                 const std::string &name);

    static Order createOrder(long long companyId,
                             const std::string &title,
                             const std::string &timeStart,
                             const std::string &duration,
                             long long employeeId);

    static Employee createEmployee(long long companyId,
                                   const std::string &fullName);

    static Client createClient(const std::string &phoneNumber,
                               const std::string &password,
                               const std::string &fullName,
                               const std::string &email);

    static long long authorizeClient(const std::string &phoneNumber,
                                     const std::string &password);

    static long long authorizeCompany(const std::string &phoneNumber,
                                      const std::string &password);

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

    static void deleteOrder(long long id);

    static std::vector<long long> listVacantOrdersOfEmployee(long long id);

    static std::vector<long long> listBookedOrdersOfEmployee(long long id);

    static std::vector<long long> listAllOrdersOfEmployee(long long id);

    static std::vector<long long> listOrdersOfClient(long long id);

    static std::vector<long long> listCompanies();

    static std::vector<long long> listEmployeesOfCompany(long long id);
};

}  // namespace db

#endif  // BTIMETABLE_SERVICE_H
