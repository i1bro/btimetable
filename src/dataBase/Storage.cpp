#include "Storage.h"
#include <nlohmann/json.hpp>

namespace dataBase {

long long Storage::giveEmployeeId() {
    return redis.incr("lastEmployeeId");
}

long long Storage::giveClientId() {
    return redis.incr("lastClientId");
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
}

void Storage::storeSchedule(const Schedule &schedule, std::string &&prefix) {
    std::string key = prefix + "schedule";
    nlohmann::json value;
    for (auto i : schedule.listVacantOrders()) {
        value["vacantOrders"].push_back(i);
    }
    for (auto i : schedule.listBookedOrders()) {
        value["bookedOrders"].push_back(i);
    }
    redis.set(key, value.dump());
}

void Storage::storeCompany(const Company &company) {
    std::string key = "Company:" + std::to_string(company.id);
    nlohmann::json value;
    value["name"] = company.name;
    for (auto i : company.listEmployees()) {
        value["employees"].push_back(i);
    }
    storeSchedule(company.getSchedule(), key + ":");
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

Company Storage::getCompanyById(long long int id) {
    std::string key = "Company:" + std::to_string(id);
    nlohmann::json value = nlohmann::json::parse(redis.get(key).value());
    nlohmann::json schedule =
        nlohmann::json::parse(redis.get(key + ":schedule").value());
    Company company(id);
    company.name = value["name"];
    for (long long i : value["employees"]) {
        company.addEmployee(i);
    }
    for (long long i : schedule["vacantOrders"]) {
        company.addVacantOrder(i);
    }
    for (long long i : schedule["bookedOrders"]) {
        company.addBookedOrder(i);
    }
    return std::move(company);
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

void Storage::addOrderToEmployee(long long int employeeId,
                                 long long int orderId) {
    std::string key = "Employee:" + std::to_string(employeeId) + ":orders";
    redis.sadd(key, std::to_string(orderId));
}

void Storage::addOrderToClient(long long int clientId, long long int orderId) {
    std::string key = "Client:" + std::to_string(clientId) + ":orders";
    redis.sadd(key, std::to_string(orderId));
}

void Storage::deleteOrderOfEmployee(long long int employeeId,
                                    long long int orderId) {
    std::string key = "Employee:" + std::to_string(employeeId) + ":orders";
    redis.srem(key, std::to_string(orderId));
}

void Storage::deleteOrderOfClient(long long int clientId,
                                  long long int orderId) {
    std::string key = "Client:" + std::to_string(clientId) + ":orders";
    redis.srem(key, std::to_string(orderId));
}

std::vector<long long> Storage::listOrdersOfEmployee(long long int employeeId) {
    std::string key = "Employee:" + std::to_string(employeeId) + ":orders";
    std::vector<long long> response;
    redis.smembers(key, std::inserter(response, response.begin()));
    return std::move(response);
}

std::vector<long long> Storage::listOrdersOfClient(long long int clientId) {
    std::string key = "Client:" + std::to_string(clientId) + ":orders";
    std::vector<long long> response;
    redis.smembers(key, std::inserter(response, response.begin()));
    return std::move(response);
}

}  // namespace dataBase