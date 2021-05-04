#ifndef BTIMETABLE_SERVICE_H
#define BTIMETABLE_SERVICE_H

#include "Entities.h"
#include "Storage.h"

namespace dataBase {

class Service {
private:
    inline static Storage storage = Storage();

public:
    Service() = default;

    static Company createCompany(std::string name);

    static Order createOrder(long long companyId,
                             std::string title,
                             long long timeStart,
                             long long duration,
                             long long employeeId);

    static Order createOrder(long long companyId,
                             std::string title,
                             long long timeStart,
                             long long duration,
                             long long clientId,
                             long long employeeId);

    static Employee createEmployee(long long companyId, std::string fullName);

    static Client createClient(std::string fullName,
                               std::string phoneNumber,
                               std::string email);

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

    // void deleteOrder(long long Id);

    // void deleteEmployee(long long Id);

    static std::vector<long long> listVacantOrdersOfEmployee(long long id);

    static std::vector<long long> listBookedOrdersOfEmployee(long long id);

    static std::vector<long long> listAllOrdersOfEmployee(long long id);

    static std::vector<long long> listOrdersOfClient(long long id);

    static std::vector<long long> listCompanies();

    static std::vector<long long> listEmployeesOfCompany(long long id);
};

}  // namespace dataBase

#endif  // BTIMETABLE_SERVICE_H
