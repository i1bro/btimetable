#pragma comment(lib, "ws2_32.lib")

#include <random>
#include "ClientAPI.h"
#include "CompanyAPI.h"
#include "Entities.h"
#include "btt/Service.h"
#include "doctest.h"

bool isIn(const std::vector<long long> &a, long long b) {
    for (auto c : a) {
        if (c == b) {
            return true;
        }
    }
    return false;
}

TEST_CASE("Create structures") {
    SUBCASE("Client") {
        auto a = db::ClientAPI::createClient("Vasya", "+7-987-654-32-10",
                                             "vasya@mail.com");
        CHECK(db::ClientAPI::listOrdersOfClient(a.id).empty());

        auto b = db::ClientAPI::getClientById(a.id);
        CHECK(a.id == b.id);
        CHECK(a.fullName == b.fullName);
        CHECK(a.email == b.email);
        CHECK(a.phoneNumber == b.phoneNumber);
    }

    SUBCASE("Company") {
        auto a = db::CompanyAPI::createCompany("Tuturu");
        CHECK(isIn(db::ClientAPI::listCompanies(), a.id));

        auto b = db::CompanyAPI::getCompanyById(a.id);
        CHECK(a.id == b.id);
        CHECK(a.name == b.name);
    }

    SUBCASE("Employee") {
        auto company = db::CompanyAPI::createCompany("Zavod");
        auto a = db::CompanyAPI::createEmployee(company.id, "Vasya");
        CHECK(isIn(db::CompanyAPI::listEmployeesOfCompany(company.id), a.id));
        CHECK(a.companyId == company.id);

        auto b = db::CompanyAPI::getEmployeeById(a.id);
        CHECK(a.id == b.id);
        CHECK(a.fullName == b.fullName);
        CHECK(a.companyId == b.companyId);
    }

    SUBCASE("Order") {
        auto company = db::CompanyAPI::createCompany("Zavod");
        auto employee = db::CompanyAPI::createEmployee(company.id, "Vasya");
        auto a = db::CompanyAPI::createOrder(company.id, "nogotochki",
                                             "2010-04-05 12:00:17", "12:00:17",
                                             employee.id);
        CHECK(
            isIn(db::CompanyAPI::listVacantOrdersOfCompany(company.id), a.id));
        CHECK(isIn(db::CompanyAPI::listVacantOrdersOfEmployee(employee.id),
                   a.id));
        CHECK(a.companyId == company.id);
        CHECK(a.employeeId == employee.id);
        CHECK(a.clientId == -1);

        auto b = db::CompanyAPI::getOrderById(a.id);
        CHECK(a.id == b.id);
        CHECK(a.title == b.title);
        CHECK(a.companyId == b.companyId);
        CHECK(a.timeStart == b.timeStart);
        CHECK(a.duration == b.duration);
        CHECK(a.employeeId == b.employeeId);
        CHECK(a.clientId == b.clientId);

        auto c = db::CompanyAPI::createOrder(company.id, "1234", "2010-04-05 12:00:17", "12:00:17", employee.id);
        auto d = db::CompanyAPI::createOrder(company.id, "1234", "2010-04-05 12:00:17", "12:00:17", employee.id);
        CHECK(
            isIn(db::CompanyAPI::listVacantOrdersOfCompany(company.id), c.id));
        CHECK(isIn(db::CompanyAPI::listVacantOrdersOfEmployee(employee.id),
                   c.id));
        CHECK(
            isIn(db::CompanyAPI::listVacantOrdersOfCompany(company.id), d.id));
        CHECK(isIn(db::CompanyAPI::listVacantOrdersOfEmployee(employee.id),
                   d.id));
    }
}

TEST_CASE("Change structures") {
    SUBCASE("Client email") {
        auto a = db::ClientAPI::createClient("Vasya", "+7-987-654-32-10",
                                             "vasya@mail.com");

        db::ClientAPI::changeClientEmail(a.id, "petya@mail.com");
        auto b = db::ClientAPI::getClientById(a.id);
        CHECK(a.id == b.id);
        CHECK(a.fullName == b.fullName);
        CHECK(b.email == "petya@mail.com");
        CHECK(a.phoneNumber == b.phoneNumber);
    }

    SUBCASE("Client fullName") {
        auto a = db::ClientAPI::createClient("Vasya", "+7-987-654-32-10",
                                             "vasya@mail.com");

        db::ClientAPI::changeClientFullName(a.id, "Petya");
        auto b = db::ClientAPI::getClientById(a.id);
        CHECK(a.id == b.id);
        CHECK(b.fullName == "Petya");
        CHECK(a.email == b.email);
        CHECK(a.phoneNumber == b.phoneNumber);
    }

    SUBCASE("Client phoneNumber") {
        auto a = db::ClientAPI::createClient("Vasya", "+7-987-654-32-10",
                                             "vasya@mail.com");

        db::ClientAPI::changeClientPhoneNumber(a.id, "+7-012-345-67-89");
        auto b = db::ClientAPI::getClientById(a.id);
        CHECK(a.id == b.id);
        CHECK(a.fullName == b.fullName);
        CHECK(a.email == b.email);
        CHECK(b.phoneNumber == "+7-012-345-67-89");
    }

    SUBCASE("Order title") {
        auto company = db::CompanyAPI::createCompany("Zavod");
        auto employee = db::CompanyAPI::createEmployee(company.id, "Vasya");
        auto a = db::CompanyAPI::createOrder(company.id, "nogotochki",
                                             "2010-04-05 12:00:17", "12:00:17",
                                             employee.id);

        db::CompanyAPI::changeOrderTitle(a.id, "-____-");
        auto b = db::CompanyAPI::getOrderById(a.id);
        CHECK(a.id == b.id);
        CHECK(b.title == "-____-");
        CHECK(a.companyId == b.companyId);
        CHECK(a.timeStart == b.timeStart);
        CHECK(a.duration == b.duration);
        CHECK(a.employeeId == b.employeeId);
        CHECK(a.clientId == b.clientId);
    }

    SUBCASE("Order timeStart") {
        auto company = db::CompanyAPI::createCompany("Zavod");
        auto employee = db::CompanyAPI::createEmployee(company.id, "Vasya");
        auto a = db::CompanyAPI::createOrder(company.id, "nogotochki",
                                             "2010-04-05 12:00:17", "12:00:17",
                                             employee.id);

        auto newValue = "2010-04-05 12:00:17";
        db::CompanyAPI::changeOrderTimeStart(a.id, newValue);
        auto b = db::CompanyAPI::getOrderById(a.id);
        CHECK(a.id == b.id);
        CHECK(a.title == b.title);
        CHECK(a.companyId == b.companyId);
        CHECK(b.timeStart == newValue);
        CHECK(a.clientId == b.clientId);
        CHECK(a.duration == b.duration);
        CHECK(a.employeeId == b.employeeId);
    }

    SUBCASE("Order duration") {
        auto company = db::CompanyAPI::createCompany("Zavod");
        auto employee = db::CompanyAPI::createEmployee(company.id, "Vasya");
        auto a = db::CompanyAPI::createOrder(company.id, "nogotochki",
                                             "2010-04-05 12:00:17", "12:00:17",
                                             employee.id);

        auto newValue = "12:00:17";
        db::CompanyAPI::changeOrderDuration(a.id, newValue);
        auto b = db::CompanyAPI::getOrderById(a.id);
        CHECK(a.id == b.id);
        CHECK(a.title == b.title);
        CHECK(a.companyId == b.companyId);
        CHECK(a.timeStart == b.timeStart);
        CHECK(a.clientId == b.clientId);
        CHECK(b.duration == newValue);
        CHECK(a.employeeId == b.employeeId);
    }

    SUBCASE("Employee fullName") {
        auto company = db::CompanyAPI::createCompany("Zavod");
        auto a = db::CompanyAPI::createEmployee(company.id, "Vasya");

        db::CompanyAPI::changeEmployeeFullName(a.id, "Petya");
        auto b = db::CompanyAPI::getEmployeeById(a.id);
        CHECK(a.id == b.id);
        CHECK(b.fullName == "Petya");
        CHECK(a.companyId == b.companyId);
    }
}

TEST_CASE("Booking and cancelling") {
    auto company = db::CompanyAPI::createCompany("Zavod");
    auto employee = db::CompanyAPI::createEmployee(company.id, "Petya");
    auto client = db::ClientAPI::createClient("Vasya", "+7-987-654-32-10",
                                              "vasya@mail.com");
    ;
    auto a = db::CompanyAPI::createOrder(
        company.id, "nogotochki", "2010-04-05 12:00:17", "12:00:17", employee.id);
    CHECK(isIn(db::CompanyAPI::listVacantOrdersOfCompany(company.id), a.id));
    CHECK(isIn(db::CompanyAPI::listVacantOrdersOfEmployee(employee.id), a.id));
    CHECK(!isIn(db::CompanyAPI::listBookedOrdersOfCompany(company.id), a.id));
    CHECK(!isIn(db::CompanyAPI::listBookedOrdersOfEmployee(employee.id), a.id));
    CHECK(!isIn(db::ClientAPI::listOrdersOfClient(client.id), a.id));
    CHECK(a.companyId == company.id);
    CHECK(a.employeeId == employee.id);
    CHECK(a.clientId == -1);

    db::ClientAPI::bookOrder(a.id, client.id);
    auto b = db::ClientAPI::getOrderById(a.id);
    CHECK(!isIn(db::CompanyAPI::listVacantOrdersOfCompany(company.id), a.id));
    CHECK(!isIn(db::CompanyAPI::listVacantOrdersOfEmployee(employee.id), a.id));
    CHECK(isIn(db::CompanyAPI::listBookedOrdersOfCompany(company.id), a.id));
    CHECK(isIn(db::CompanyAPI::listBookedOrdersOfEmployee(employee.id), a.id));
    CHECK(isIn(db::ClientAPI::listOrdersOfClient(client.id), a.id));
    CHECK(b.companyId == company.id);
    CHECK(b.employeeId == employee.id);
    CHECK(b.clientId == client.id);

    db::ClientAPI::cancelOrder(a.id);
    auto c = db::ClientAPI::getOrderById(a.id);
    CHECK(isIn(db::CompanyAPI::listVacantOrdersOfCompany(company.id), a.id));
    CHECK(isIn(db::CompanyAPI::listVacantOrdersOfEmployee(employee.id), a.id));
    CHECK(!isIn(db::CompanyAPI::listBookedOrdersOfCompany(company.id), a.id));
    CHECK(!isIn(db::CompanyAPI::listBookedOrdersOfEmployee(employee.id), a.id));
    CHECK(!isIn(db::ClientAPI::listOrdersOfClient(client.id), a.id));
    CHECK(c.companyId == company.id);
    CHECK(c.employeeId == employee.id);
    CHECK(c.clientId == -1);
}
