#ifndef BTIMETABLE_CLIENTAPI_H
#define BTIMETABLE_CLIENTAPI_H

class ClientAPI {
public:
    Client createClient(std::string fullName);

    std::vector<long long> listCompanies();

    std::vector<long long> listVacantOrders(long long id);

    void bookOrder(long long id);

    Client getClientById(long long id);

    Order getOrderById(long long id);

    Employee getEmployeeById(long long id);

    Company getCompanyById(long long id);

    std::vector<long long> listOrdersOfClient(long long clientId);
};

#endif //BTIMETABLE_CLIENTAPI_H
