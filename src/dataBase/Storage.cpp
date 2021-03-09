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

void Storage::storeEmployee(const Employee &employee) {
    std::string key = "Employee:" + std::to_string(employee.id);
    nlohmann::json value;
    value["fullName"] = employee.fullName;
    redis.set(key, value.dump());
}

void Storage::storeClient(const Client &client) {
    std::string key = "Client:" + std::to_string(client.id);
    nlohmann::json value;
    value["fullName"] = client.fullName;
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
    std::string key = "Company:" + company.name;
    nlohmann::json value;
    for (auto i : company.listEmployees()) {
        value["employees"].push_back(i);
    }
    storeSchedule(company.getSchedule(), key + ":");
    redis.set(key, value.dump());
}

Employee Storage::getEmployeeById(long long id) {
    std::string key = "Employee:" + std::to_string(id);
    nlohmann::json value = nlohmann::json::parse(redis.get(key));
    Employee employee(id);
    employee.fullName = value["fullName"];
    return std::move(employee);
}

Client Storage::getClientById(long long id) {
    std::string key = "Client:" + std::to_string(id);
    nlohmann::json value = nlohmann::json::parse(redis.get(key));
    Client client(id);
    client.fullName = value["fullName"];
    return std::move(client);
}

Order Storage::getOrderById(long long id) {
    std::string key = "Order:" + std::to_string(id);
    nlohmann::json value = nlohmann::json::parse(redis.get(key));
    Order order(id);
    order.title = value["title"];
    order.timeStart = value["timeStart"];
    order.duration = value["duration"];
    order.clientId = value["clientId"];
    order.employeeId = value["employeeId"];
    return std::move(order);
}

Company Storage::getCompanyByName(std::string name) {
    std::string key = "Order:" + name;
    nlohmann::json value = nlohmann::json::parse(redis.get(key));
    nlohmann::json schedule =
        nlohmann::json::parse(redis.get(key + ":schedule"));
    Company company(std::move(name));
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

void Storage::setEmployeesCompany(long long int employeeId,
                                  const std::string &companyName) {
    std::string key = "Employee:" + std::to_string(employeeId) + ":companyName";
    redis.set(key, companyName);
}

void Storage::setOrdersCompany(long long int orderId,
                               const std::string &companyName) {
    std::string key = "Order:" + std::to_string(orderId) + ":companyName";
    redis.set(key, companyName);
}

std::string Storage::getEmployeesCompany(long long employeeId) {
    std::string key = "Employee:" + std::to_string(employeeId) + ":companyName";
    std::string response = redis.get(key).value();
    return std::move(response);
}

std::string Storage::getOrdersCompany(long long orderId) {
    std::string key = "Order:" + std::to_string(orderId) + ":companyName";
    std::string response = redis.get(key).value();
    return std::move(response);
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