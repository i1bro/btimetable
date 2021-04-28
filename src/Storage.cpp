#include "btt/Storage.h"
#include <nlohmann/json.hpp>

namespace dataBase {

long long Storage::giveEmployeeId() {
    return redis.incr("lastEmployeeId");
}

long long Storage::giveClientId() {
    long long id = redis.incr("lastClientId");
    redis.sadd("CompanyList", std::to_string(id));
    return id;
}

long long Storage::giveOrderId() {
    return redis.incr("lastEmployeeId");
}

long long Storage::giveCompanyId() {
    return redis.incr("lastCompanyId");
}

void Storage::storeEmployee(const Employee &employee) {
    std::string key = "Employee:" + std::to_string(employee.id);
    nlohmann::json value;
    value["fullName"] = employee.fullName;
    redis.set(key, value.dump());
    redis.set(key + ":companyId", std::to_string(employee.companyId));
    redis.sadd("Company:" + std::to_string(employee.companyId) + ":employees",
               std::to_string(employee.id));
}

void Storage::storeClient(const Client &client) {
    std::string key = "Client:" + std::to_string(client.id);
    nlohmann::json value;
    value["fullName"] = client.fullName;
    value["phoneNumber"] = client.phoneNumber;
    value["email"] = client.email;
    redis.set(key, value.dump());
}

void Storage::storeOrder(const Order &order) {
    std::string key = "Order:" + std::to_string(order.id);
    nlohmann::json value;
    value["title"] = order.title;
    value["timeStart"] = order.timeStart;
    value["duration"] = order.duration;
    value["clientId"] = order.clientId;
    value["employeeId"] = order.employeeId;
    redis.set(key, value.dump());
    redis.set(key + ":companyId", std::to_string(order.companyId));
    if (order.employeeId == -1) {
        redis.sadd(
            "Company:" + std::to_string(order.companyId) + ":vacantOrders",
            std::to_string(order.id));
        redis.sadd(
            "Employee:" + std::to_string(order.employeeId) + ":vacantOrders",
            std::to_string(order.id));
        redis.srem(
            "Company:" + std::to_string(order.companyId) + ":bookedOrders",
            std::to_string(order.id));
        redis.srem(
            "Employee:" + std::to_string(order.employeeId) + ":bookedOrders",
            std::to_string(order.id));
    } else {
        redis.sadd("Client:" + std::to_string(order.clientId) + ":orders",
                   std::to_string(order.id));
        redis.sadd(
            "Company:" + std::to_string(order.companyId) + ":bookedOrders",
            std::to_string(order.id));
        redis.sadd(
            "Employee:" + std::to_string(order.employeeId) + ":bookedOrders",
            std::to_string(order.id));
        redis.srem(
            "Company:" + std::to_string(order.companyId) + ":vacantOrders",
            std::to_string(order.id));
        redis.srem(
            "Employee:" + std::to_string(order.employeeId) + ":vacantOrders",
            std::to_string(order.id));
    }
}

void Storage::storeCompany(const Company &company) {
    std::string key = "Company:" + std::to_string(company.id);
    nlohmann::json value;
    value["name"] = company.name;
    redis.set(key, value.dump());
}

Employee Storage::getEmployeeById(long long id) {
    std::string key = "Employee:" + std::to_string(id);
    nlohmann::json value = nlohmann::json::parse(redis.get(key).value());
    Employee employee(id);
    employee.companyId = std::stoll(redis.get(key + ":companyId").value());
    employee.fullName = value["fullName"];
    return std::move(employee);
}

Client Storage::getClientById(long long id) {
    std::string key = "Client:" + std::to_string(id);
    nlohmann::json value = nlohmann::json::parse(redis.get(key).value());
    Client client(id);
    client.fullName = value["fullName"];
    client.phoneNumber = value["phoneNumber"];
    client.email = value["email"];
    return std::move(client);
}

Order Storage::getOrderById(long long id) {
    std::string key = "Order:" + std::to_string(id);
    nlohmann::json value = nlohmann::json::parse(redis.get(key).value());
    Order order(id);
    order.companyId = std::stoll(redis.get(key + ":companyId").value());
    order.title = value["title"];
    order.timeStart = value["timeStart"];
    order.duration = value["duration"];
    order.clientId = value["clientId"];
    order.employeeId = value["employeeId"];
    return std::move(order);
}

Company Storage::getCompanyById(long long id) {
    std::string key = "Company:" + std::to_string(id);
    nlohmann::json value = nlohmann::json::parse(redis.get(key).value());
    Company company(id);
    company.name = value["name"];
    return std::move(company);
}

void Storage::deleteEmployee(long long id) {
    /*std::string key = "Employee:" + std::to_string(id);
    redis.del(key);
    std::string companyId = redis.get(key + ":companyId").value();
    redis.del(key + ":companyId");
    redis.srem("Company:" + companyId + ":employees", std::to_string(id));*/
    // TODO
}

void Storage::deleteClient(long long id) {
    // TODO
}

void Storage::deleteOrder(long long id) {
    // TODO
}

void Storage::deleteCompany(long long id) {
    // TODO
}

long long Storage::getEmployeeOwner(long long employeeId) {
    std::string key = "Employee:" + std::to_string(employeeId) + ":companyId";
    std::string response = redis.get(key).value();
    return std::stoll(response);
}

long long Storage::getOrderOwner(long long orderId) {
    std::string key = "Order:" + std::to_string(orderId) + ":companyId";
    std::string response = redis.get(key).value();
    return std::stoll(response);
}

void Storage::deleteOrderOfClient(long long int clientId,
                                  long long int orderId) {
    std::string key = "Client:" + std::to_string(clientId) + ":orders";
    redis.srem(key, std::to_string(orderId));
}

std::vector<long long> Storage::listVacantOrdersOfCompany(
    long long employeeId) {
    std::string key = "Company:" + std::to_string(employeeId) + ":vacantOrders";
    std::vector<std::string> response;
    redis.smembers(key, std::inserter(response, response.begin()));
    std::vector<long long> ans;
    for (auto &i : response) {
        ans.push_back(stoll(i));
    }
    return std::move(ans);
}

std::vector<long long> Storage::listBookedOrdersOfCompany(
    long long employeeId) {
    std::string key = "Company:" + std::to_string(employeeId) + ":bookedOrders";
    std::vector<std::string> response;
    redis.smembers(key, std::inserter(response, response.begin()));
    std::vector<long long> ans;
    for (auto &i : response) {
        ans.push_back(stoll(i));
    }
    return std::move(ans);
}

std::vector<long long> Storage::listVacantOrdersOfEmployee(
    long long employeeId) {
    std::string key =
        "Employee:" + std::to_string(employeeId) + ":vacantOrders";
    std::vector<std::string> response;
    redis.smembers(key, std::inserter(response, response.begin()));
    std::vector<long long> ans;
    for (auto &i : response) {
        ans.push_back(stoll(i));
    }
    return std::move(ans);
}

std::vector<long long> Storage::listBookedOrdersOfEmployee(
    long long employeeId) {
    std::string key =
        "Employee:" + std::to_string(employeeId) + ":bookedOrders";
    std::vector<std::string> response;
    redis.smembers(key, std::inserter(response, response.begin()));
    std::vector<long long> ans;
    for (auto &i : response) {
        ans.push_back(stoll(i));
    }
    return std::move(ans);
}

std::vector<long long> Storage::listOrdersOfClient(long long int clientId) {
    std::string key = "Client:" + std::to_string(clientId) + ":orders";
    std::vector<std::string> response;
    redis.smembers(key, std::inserter(response, response.begin()));
    std::vector<long long> ans;
    for (auto &i : response) {
        ans.push_back(stoll(i));
    }
    return std::move(ans);
}

std::vector<long long> Storage::listCompanies() {
    std::string key = "ClientList";
    std::vector<std::string> response;
    redis.smembers(key, std::inserter(response, response.begin()));
    std::vector<long long> ans;
    for (auto &i : response) {
        ans.push_back(stoll(i));
    }
    return std::move(ans);
}

std::vector<long long> Storage::listEmployeesOfCompany(long long int id) {
    std::string key = "Company:" + std::to_string(id) + ":employees";
    std::vector<std::string> response;
    redis.smembers(key, std::inserter(response, response.begin()));
    std::vector<long long> ans;
    for (auto &i : response) {
        ans.push_back(stoll(i));
    }
    return std::move(ans);
}

}  // namespace dataBase