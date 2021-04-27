#ifndef BTIMETABLE_CLIENTAPI_H
#define BTIMETABLE_CLIENTAPI_H

class ClientAPI {
public:
    Client createClient(std::string fullName, std::string phoneNumber, std::string email);

    std::vector<long long> listCompanies();

    std::vector<long long> listVacantOrdersOfCompany(long long id);

    std::vector<long long> listEmployeesOfCompany(long long id);

    void bookOrder(long long orderId, long long clientId);

    void cancelOrder(long long orderId);

    Client getClientById(long long id);

    Order getOrderById(long long id);

    Employee getEmployeeById(long long id);

    Company getCompanyById(long long id);

    void changeClientFullName(long long id, std::string fullName);

    void changeClientPhoneNumber(long long id, std::string phoneNumber);

    void changeClientEmail(long long id, std::string email);

    std::vector<long long> listOrdersOfClient(long long id);

    std::vector<long long> listVacantOrdersOfEmployee(long long id);
};

#endif //BTIMETABLE_CLIENTAPI_H
