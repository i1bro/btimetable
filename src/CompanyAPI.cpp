#include "CompanyAPI.h"
#include "btt/Service.h"

namespace db {

namespace {
const std::string role = "company";

struct bttCompanyPermissionError : bttError {
    explicit bttCompanyPermissionError(const std::string &s)
        : bttError("This " + s + " does not belong your company") {
    }
};
}  // namespace

std::string CompanyAPI::createCompany(const std::string &phoneNumber,
                                      const std::string &password,
                                      const std::string &name) {
    return Service::createToken(
        Service::createCompany(phoneNumber, password, name), role);
}

long long CompanyAPI::createOrder(const std::string &token,
                                  const std::string &title,
                                  long long timeStart,
                                  long long duration,
                                  long long employeeId) {
    auto parsed = Service::verifyToken(token, role);
    return Service::createOrder(parsed, title, timeStart, duration, employeeId);
}

long long CompanyAPI::createEmployee(const std::string &token,
                                     const std::string &fullName) {
    auto parsed = Service::verifyToken(token, role);
    return Service::createEmployee(parsed, fullName);
}

std::vector<long long> CompanyAPI::listVacantOrdersOfCompany(
    const std::string &token) {
    auto parsed = Service::verifyToken(token, role);
    return Service::listVacantOrdersOfCompany(parsed);
}

std::vector<long long> CompanyAPI::listBookedOrdersOfCompany(
    const std::string &token) {
    auto parsed = Service::verifyToken(token, role);
    return Service::listBookedOrdersOfCompany(parsed);
}

std::vector<long long> CompanyAPI::listAllOrdersOfCompany(
    const std::string &token) {
    auto parsed = Service::verifyToken(token, role);
    return Service::listAllOrdersOfCompany(parsed);
}

Order CompanyAPI::getOrderById(const std::string &token, long long orderId) {
    auto parsed = Service::verifyToken(token, role);
    auto order = Service::getOrderById(orderId);
    if (order.companyId != parsed) {
        throw bttCompanyPermissionError("order");
    }
    return std::move(order);
}

Employee CompanyAPI::getEmployeeById(const std::string &token,
                                     long long employeeId) {
    auto parsed = Service::verifyToken(token, role);
    auto employee = Service::getEmployeeById(employeeId);
    if (employee.companyId != parsed) {
        throw bttCompanyPermissionError("employee");
    }
    return std::move(employee);
}

Company CompanyAPI::getCompany(const std::string &token) {
    auto parsed = Service::verifyToken(token, role);
    return Service::getCompanyById(parsed);
}

void CompanyAPI::changeOrderTitle(const std::string &token,
                                  long long orderId,
                                  std::string title) {
    auto parsed = Service::verifyToken(token, role);
    auto order = Service::getOrderById(orderId);
    if (order.companyId != parsed) {
        throw bttCompanyPermissionError("order");
    }
    order.title = std::move(title);
    Service::saveOrder(order);
}

void CompanyAPI::changeOrderTimeStart(const std::string &token,
                                      long long orderId,
                                      long long timeStart) {
    auto parsed = Service::verifyToken(token, role);
    auto order = Service::getOrderById(orderId);
    if (order.companyId != parsed) {
        throw bttCompanyPermissionError("order");
    }
    order.timeStart = timeStart;
    Service::saveOrder(order);
}

void CompanyAPI::changeOrderDuration(const std::string &token,
                                     long long orderId,
                                     long long duration) {
    auto parsed = Service::verifyToken(token, role);
    auto order = Service::getOrderById(orderId);
    if (order.companyId != parsed) {
        throw bttCompanyPermissionError("order");
    }
    order.duration = duration;
    Service::saveOrder(order);
}

void CompanyAPI::changeEmployeeFullName(const std::string &token,
                                        long long employeeId,
                                        std::string fullName) {
    auto parsed = Service::verifyToken(token, role);
    auto employee = Service::getEmployeeById(employeeId);
    if (employee.companyId != parsed) {
        throw bttCompanyPermissionError("employee");
    }
    employee.fullName = std::move(fullName);
    Service::saveEmployee(employee);
}

void CompanyAPI::deleteEmployee(const std::string &token,
                                long long employeeId) {
    auto parsed = Service::verifyToken(token, role);
    auto employee = Service::getEmployeeById(employeeId);
    if (employee.companyId != parsed) {
        throw bttCompanyPermissionError("employee");
    }
    if (!Service::listBookedOrdersOfEmployee(employeeId).empty()) {
        throw bttError(
            "Can't delete this employee: it has some booked orders.");
    }
    Service::deleteEmployee(employeeId);
}

void CompanyAPI::deleteOrder(const std::string &token, long long orderId) {
    auto parsed = Service::verifyToken(token, role);
    auto order = Service::getOrderById(orderId);
    if (order.companyId != parsed) {
        throw bttCompanyPermissionError("order");
    }
    if (order.status != Order::vacant) {
        throw bttError(
            "Can't delete this order: it is booked or already deleted.");
    }
    Service::deleteOrder(orderId);
}

std::vector<long long> CompanyAPI::listVacantOrdersOfEmployee(
    const std::string &token,
    long long employeeId) {
    auto parsed = Service::verifyToken(token, role);
    auto employee = Service::getEmployeeById(employeeId);
    if (employee.companyId != parsed) {
        throw bttCompanyPermissionError("employee");
    }
    return Service::listVacantOrdersOfEmployee(employeeId);
}

std::vector<long long> CompanyAPI::listBookedOrdersOfEmployee(
    const std::string &token,
    long long employeeId) {
    auto parsed = Service::verifyToken(token, role);
    auto employee = Service::getEmployeeById(employeeId);
    if (employee.companyId != parsed) {
        throw bttCompanyPermissionError("employee");
    }
    return Service::listBookedOrdersOfEmployee(employeeId);
}

std::vector<long long> CompanyAPI::listAllOrdersOfEmployee(
    const std::string &token,
    long long employeeId) {
    auto parsed = Service::verifyToken(token, role);
    auto employee = Service::getEmployeeById(employeeId);
    if (employee.companyId != parsed) {
        throw bttCompanyPermissionError("employee");
    }
    return Service::listAllOrdersOfEmployee(employeeId);
}

std::vector<long long> CompanyAPI::listEmployeesOfCompany(
    const std::string &token,
    sortParam sorted) {
    auto parsed = Service::verifyToken(token, role);
    return Service::listEmployeesOfCompany(parsed, sorted);
}

std::string CompanyAPI::authorizeCompany(const std::string &phoneNumber,
                                         const std::string &password) {
    return Service::createToken(
        Service::authorizeCompany(phoneNumber, password), role);
}

}  // namespace db