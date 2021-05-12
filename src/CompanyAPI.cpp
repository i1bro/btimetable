#include "CompanyAPI.h"

#include <utility>
#include "btt/Service.h"

namespace db {

Company CompanyAPI::createCompany(const std::string& name) {
    return Service::createCompany(name);
}

Order CompanyAPI::createOrder(long long companyId,
                              const std::string& title,
                              const std::string& timeStart,
                              const std::string& duration,
                              long long employeeId) {
    return Service::createOrder(companyId, title, timeStart,
                                duration, employeeId);
}

Employee CompanyAPI::createEmployee(long long companyId, const std::string& fullName) {
    return Service::createEmployee(companyId, fullName);
}

std::vector<long long> CompanyAPI::listVacantOrdersOfCompany(long long id) {
    return Service::listVacantOrdersOfCompany(id);
}

std::vector<long long> CompanyAPI::listBookedOrdersOfCompany(long long id) {
    return Service::listBookedOrdersOfCompany(id);
}

std::vector<long long> CompanyAPI::listAllOrdersOfCompany(long long id) {
    return Service::listAllOrdersOfCompany(id);
}

Order CompanyAPI::getOrderById(long long id) {
    return Service::getOrderById(id);
}

Employee CompanyAPI::getEmployeeById(long long id) {
    return Service::getEmployeeById(id);
}

Company CompanyAPI::getCompanyById(long long id) {
    return Service::getCompanyById(id);
}

void CompanyAPI::changeOrderTitle(long long id, std::string title) {
    auto order = Service::getOrderById(id);
    order.title = std::move(title);
    Service::saveOrder(order);
}

void CompanyAPI::changeOrderTimeStart(long long id, std::string timeStart) {
    auto order = Service::getOrderById(id);
    order.timeStart = std::move(timeStart);
    Service::saveOrder(order);
}

void CompanyAPI::changeOrderDuration(long long id, std::string duration) {
    auto order = Service::getOrderById(id);
    order.duration = std::move(duration);
    Service::saveOrder(order);
}

void CompanyAPI::changeEmployeeFullName(long long id, std::string fullName) {
    auto employee = Service::getEmployeeById(id);
    employee.fullName = std::move(fullName);
    Service::saveEmployee(employee);
}

std::vector<long long> CompanyAPI::listVacantOrdersOfEmployee(long long id) {
    return Service::listVacantOrdersOfEmployee(id);
}

std::vector<long long> CompanyAPI::listBookedOrdersOfEmployee(long long id) {
    return Service::listBookedOrdersOfEmployee(id);
}

std::vector<long long> CompanyAPI::listAllOrdersOfEmployee(long long id) {
    return Service::listAllOrdersOfEmployee(id);
}

std::vector<long long> CompanyAPI::listEmployeesOfCompany(long long id) {
    return Service::listEmployeesOfCompany(id);
}
}  // namespace db