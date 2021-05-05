#ifndef BTIMETABLE_CLIENTAPI_H
#define BTIMETABLE_CLIENTAPI_H

#include "Entities.h"

namespace db {
class ClientAPI {
public:
    static Client createClient(std::string fullName,
                               std::string phoneNumber,
                               std::string email);

    static std::vector<long long> listCompanies();

    static std::vector<long long> listVacantOrdersOfCompany(long long id);

    static std::vector<long long> listEmployeesOfCompany(long long id);

    static void bookOrder(long long orderId, long long clientId);

    static void cancelOrder(long long orderId);

    static Client getClientById(long long id);

    static Order getOrderById(long long id);

    static Employee getEmployeeById(long long id);

    static Company getCompanyById(long long id);

    static void changeClientFullName(long long id, std::string fullName);

    static void changeClientPhoneNumber(long long id, std::string phoneNumber);

    static void changeClientEmail(long long id, std::string email);

    static std::vector<long long> listOrdersOfClient(long long id);

    static std::vector<long long> listVacantOrdersOfEmployee(long long id);
};
}  // namespace db

#endif  // BTIMETABLE_CLIENTAPI_H
