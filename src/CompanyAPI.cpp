#include "CompanyAPI.h"
#include "btt/Service.h"

namespace db {

std::string CompanyAPI::createCompany(const std::string &phoneNumber,
                                      const std::string &password,
                                      const std::string &name) {
    return Service::createToken(
        Service::createCompany(phoneNumber, password, name), "company");
}

long long CompanyAPI::createOrder(const std::string &token,
                                  const std::string &title,
                                  long long timeStart,
                                  long long duration,
                                  long long employeeId) {
    auto parsed = Service::verifyToken(token);
    if (parsed.second != "company") {
        throw std::exception();  // TODO
    }
    return Service::createOrder(parsed.first, title, timeStart, duration,
                                employeeId);
}

long long CompanyAPI::createEmployee(const std::string &token,
                                     const std::string &fullName) {
    auto parsed = Service::verifyToken(token);
    if (parsed.second != "company") {
        throw std::exception();  // TODO
    }
    return Service::createEmployee(parsed.first, fullName);
}

std::vector<long long> CompanyAPI::listVacantOrdersOfCompany(
    const std::string &token) {
    auto parsed = Service::verifyToken(token);
    if (parsed.second != "company") {
        throw std::exception();  // TODO
    }
    return Service::listVacantOrdersOfCompany(parsed.first);
}

std::vector<long long> CompanyAPI::listBookedOrdersOfCompany(
    const std::string &token) {
    auto parsed = Service::verifyToken(token);
    if (parsed.second != "company") {
        throw std::exception();  // TODO
    }
    return Service::listBookedOrdersOfCompany(parsed.first);
}

std::vector<long long> CompanyAPI::listAllOrdersOfCompany(
    const std::string &token) {
    auto parsed = Service::verifyToken(token);
    if (parsed.second != "company") {
        throw std::exception();  // TODO
    }
    return Service::listAllOrdersOfCompany(parsed.first);
}

Order CompanyAPI::getOrderById(const std::string &token, long long orderId) {
    auto parsed = Service::verifyToken(token);
    if (parsed.second != "company") {
        throw std::exception();  // TODO
    }
    auto order = Service::getOrderById(orderId);
    if (order.companyId != parsed.first) {
        throw std::exception();  // TODO
    }
    return std::move(order);
}

Employee CompanyAPI::getEmployeeById(const std::string &token,
                                     long long employeeId) {
    auto parsed = Service::verifyToken(token);
    if (parsed.second != "company") {
        throw std::exception();  // TODO
    }
    auto employee = Service::getEmployeeById(employeeId);
    if (employee.companyId != parsed.first) {
        throw std::exception();  // TODO
    }
    return std::move(employee);
}

Company CompanyAPI::getCompany(const std::string &token) {
    auto parsed = Service::verifyToken(token);
    if (parsed.second != "company") {
        throw std::exception();  // TODO
    }
    return Service::getCompanyById(parsed.first);
}

void CompanyAPI::changeOrderTitle(const std::string &token,
                                  long long orderId,
                                  std::string title) {
    auto parsed = Service::verifyToken(token);
    if (parsed.second != "company") {
        throw std::exception();  // TODO
    }
    auto order = Service::getOrderById(orderId);
    if (order.companyId != parsed.first) {
        throw std::exception();  // TODO
    }
    order.title = std::move(title);
    Service::saveOrder(order);
}

void CompanyAPI::changeOrderTimeStart(const std::string &token,
                                      long long orderId,
                                      long long timeStart) {
    auto parsed = Service::verifyToken(token);
    if (parsed.second != "company") {
        throw std::exception();  // TODO
    }
    auto order = Service::getOrderById(orderId);
    if (order.companyId != parsed.first) {
        throw std::exception();  // TODO
    }
    order.timeStart = timeStart;
    Service::saveOrder(order);
}

void CompanyAPI::changeOrderDuration(const std::string &token,
                                     long long orderId,
                                     long long duration) {
    auto parsed = Service::verifyToken(token);
    if (parsed.second != "company") {
        throw std::exception();  // TODO
    }
    auto order = Service::getOrderById(orderId);
    if (order.companyId != parsed.first) {
        throw std::exception();  // TODO
    }
    order.duration = duration;
    Service::saveOrder(order);
}

void CompanyAPI::changeEmployeeFullName(const std::string &token,
                                        long long employeeId,
                                        std::string fullName) {
    auto parsed = Service::verifyToken(token);
    if (parsed.second != "company") {
        throw std::exception();  // TODO
    }
    auto employee = Service::getEmployeeById(employeeId);
    if (employee.companyId != parsed.first) {
        throw std::exception();  // TODO
    }
    employee.fullName = std::move(fullName);
    Service::saveEmployee(employee);
}

void CompanyAPI::deleteEmployee(const std::string &token, long long int employeeId) {
    auto parsed = Service::verifyToken(token);
    if (parsed.second != "company") {
        throw std::exception();  // TODO
    }
    auto employee = Service::getOrderById(employeeId);
    if (employee.companyId != parsed.first || !Service::listBookedOrdersOfEmployee(employeeId).empty()) {
        throw std::exception();  // TODO
    }
    Service::deleteEmployee(employeeId);
}

void CompanyAPI::deleteOrder(const std::string &token, long long orderId) {
    auto parsed = Service::verifyToken(token);
    if (parsed.second != "company") {
        throw std::exception();  // TODO
    }
    auto order = Service::getOrderById(orderId);
    if (order.companyId != parsed.first || order.status != Order::vacant) {
        throw std::exception();  // TODO
    }
    Service::deleteOrder(orderId);
}

std::vector<long long> CompanyAPI::listVacantOrdersOfEmployee(
    const std::string &token,
    long long employeeId) {
    auto parsed = Service::verifyToken(token);
    if (parsed.second != "company") {
        throw std::exception();  // TODO
    }
    auto employee = Service::getEmployeeById(employeeId);
    if (employee.companyId != parsed.first) {
        throw std::exception();  // TODO
    }
    return Service::listVacantOrdersOfEmployee(employeeId);
}

std::vector<long long> CompanyAPI::listBookedOrdersOfEmployee(
    const std::string &token,
    long long employeeId) {
    auto parsed = Service::verifyToken(token);
    if (parsed.second != "company") {
        throw std::exception();  // TODO
    }
    auto employee = Service::getEmployeeById(employeeId);
    if (employee.companyId != parsed.first) {
        throw std::exception();  // TODO
    }
    return Service::listBookedOrdersOfEmployee(employeeId);
}

std::vector<long long> CompanyAPI::listAllOrdersOfEmployee(
    const std::string &token,
    long long employeeId) {
    auto parsed = Service::verifyToken(token);
    if (parsed.second != "company") {
        throw std::exception();  // TODO
    }
    auto employee = Service::getEmployeeById(employeeId);
    if (employee.companyId != parsed.first) {
        throw std::exception();  // TODO
    }
    return Service::listAllOrdersOfEmployee(employeeId);
}

std::vector<long long> CompanyAPI::listEmployeesOfCompany(
    const std::string &token) {
    auto parsed = Service::verifyToken(token);
    if (parsed.second != "company") {
        throw std::exception();  // TODO
    }
    return Service::listEmployeesOfCompany(parsed.first);
}

std::string CompanyAPI::authorizeCompany(const std::string &phoneNumber,
                                         const std::string &password) {
    return Service::createToken(
        Service::authorizeCompany(phoneNumber, password), "company");
}

}  // namespace db