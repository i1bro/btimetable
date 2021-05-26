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
        auto id = db::ClientAPI::createClient("+7-987-654-32-10", "password",
                                              "Vasya", "vasya@mail.com");
        CHECK(db::ClientAPI::listOrdersOfClient(id).empty());

        auto b = db::ClientAPI::getClientById(id);
        CHECK(id == b.id);
        CHECK("Vasya" == b.fullName);
        CHECK("vasya@mail.com" == b.email);
        CHECK("+7-987-654-32-10" == b.phoneNumber);
    }

    SUBCASE("Company") {
        auto id = db::CompanyAPI::createCompany("+7-987-654-32-11", "password",
                                                "Tuturu");
        CHECK(isIn(db::ClientAPI::listCompanies(), id));

        auto b = db::CompanyAPI::getCompanyById(id);
        CHECK(id == b.id);
        CHECK("Tuturu" == b.name);
    }

    SUBCASE("Employee") {
        auto company = db::CompanyAPI::createCompany("+7-987-654-32-12",
                                                     "password", "Zavod");
        auto id = db::CompanyAPI::createEmployee(company, "Vasya");
        CHECK(isIn(db::CompanyAPI::listEmployeesOfCompany(company), id));

        auto b = db::CompanyAPI::getEmployeeById(id);
        CHECK(id == b.id);
        CHECK("Vasya" == b.fullName);
        CHECK(company == b.companyId);
    }

    SUBCASE("Order") {
        auto company = db::CompanyAPI::createCompany("+7-987-654-32-13",
                                                     "password", "Zavod");
        auto employee = db::CompanyAPI::createEmployee(company, "Vasya");
        auto id =
            db::CompanyAPI::createOrder(company, "nogotochki", 1, 2, employee);
        CHECK(isIn(db::CompanyAPI::listVacantOrdersOfCompany(company), id));
        CHECK(isIn(db::CompanyAPI::listVacantOrdersOfEmployee(employee), id));

        auto b = db::CompanyAPI::getOrderById(id);
        CHECK(id == b.id);
        CHECK("nogotochki" == b.title);
        CHECK(company == b.companyId);
        CHECK(1 == b.timeStart);
        CHECK(2 == b.duration);
        CHECK(employee == b.employeeId);
        CHECK(-1 == b.clientId);

        auto c = db::CompanyAPI::createOrder(company, "1234", 1, 2, employee);
        auto d = db::CompanyAPI::createOrder(company, "1234", 1, 2, employee);
        CHECK(isIn(db::CompanyAPI::listVacantOrdersOfCompany(company), c));
        CHECK(isIn(db::CompanyAPI::listVacantOrdersOfEmployee(employee), c));
        CHECK(isIn(db::CompanyAPI::listVacantOrdersOfCompany(company), d));
        CHECK(isIn(db::CompanyAPI::listVacantOrdersOfEmployee(employee), d));
    }
}

TEST_CASE("Change structures") {
    SUBCASE("Client email") {
        auto id = db::ClientAPI::createClient("+7-987-654-32-14", "password",
                                              "Vasya", "vasya@mail.com");

        db::ClientAPI::changeClientEmail(id, "petya@mail.com");
        auto b = db::ClientAPI::getClientById(id);
        CHECK(id == b.id);
        CHECK("Vasya" == b.fullName);
        CHECK(b.email == "petya@mail.com");
        CHECK("+7-987-654-32-14" == b.phoneNumber);
    }

    SUBCASE("Client fullName") {
        auto id = db::ClientAPI::createClient("+7-987-654-32-15", "password",
                                              "Vasya", "vasya@mail.com");

        db::ClientAPI::changeClientFullName(id, "Petya");
        auto b = db::ClientAPI::getClientById(id);
        CHECK(id == b.id);
        CHECK(b.fullName == "Petya");
        CHECK("vasya@mail.com" == b.email);
        CHECK("+7-987-654-32-15" == b.phoneNumber);
    }

    SUBCASE("Client phoneNumber") {
        auto id = db::ClientAPI::createClient("+7-987-654-32-16", "password",
                                              "Vasya", "vasya@mail.com");

        db::ClientAPI::changeClientPhoneNumber(id, "+7-012-345-67-89");
        auto b = db::ClientAPI::getClientById(id);
        CHECK(id == b.id);
        CHECK("Vasya" == b.fullName);
        CHECK("vasya@mail.com" == b.email);
        CHECK(b.phoneNumber == "+7-012-345-67-89");
    }

    SUBCASE("Order title") {
        auto company = db::CompanyAPI::createCompany("+7-987-654-32-17",
                                                     "password", "Zavod");
        auto employee = db::CompanyAPI::createEmployee(company, "Vasya");
        auto id =
            db::CompanyAPI::createOrder(company, "nogotochki", 1, 2, employee);

        db::CompanyAPI::changeOrderTitle(id, "-____-");
        auto b = db::CompanyAPI::getOrderById(id);
        CHECK(id == b.id);
        CHECK(b.title == "-____-");
        CHECK(company == b.companyId);
        CHECK(1 == b.timeStart);
        CHECK(2 == b.duration);
        CHECK(employee == b.employeeId);
        CHECK(-1 == b.clientId);
    }

    SUBCASE("Order timeStart") {
        auto company = db::CompanyAPI::createCompany("+7-987-654-32-18",
                                                     "password", "Zavod");
        auto employee = db::CompanyAPI::createEmployee(company, "Vasya");
        auto id =
            db::CompanyAPI::createOrder(company, "nogotochki", 1, 2, employee);

        auto newValue = 3;
        db::CompanyAPI::changeOrderTimeStart(id, newValue);
        auto b = db::CompanyAPI::getOrderById(id);
        CHECK(id == b.id);
        CHECK("nogotochki" == b.title);
        CHECK(company == b.companyId);
        CHECK(b.timeStart == newValue);
        CHECK(2 == b.duration);
        CHECK(employee == b.employeeId);
        CHECK(-1 == b.clientId);
    }

    SUBCASE("Order duration") {
        auto company = db::CompanyAPI::createCompany("+7-987-654-32-19",
                                                     "password", "Zavod");
        auto employee = db::CompanyAPI::createEmployee(company, "Vasya");
        auto id =
            db::CompanyAPI::createOrder(company, "nogotochki", 1, 2, employee);

        auto newValue = 3;
        db::CompanyAPI::changeOrderDuration(id, newValue);
        auto b = db::CompanyAPI::getOrderById(id);
        CHECK(id == b.id);
        CHECK("nogotochki" == b.title);
        CHECK(company == b.companyId);
        CHECK(b.timeStart == 1);
        CHECK(newValue == b.duration);
        CHECK(employee == b.employeeId);
        CHECK(-1 == b.clientId);
    }

    SUBCASE("Employee fullName") {
        auto company = db::CompanyAPI::createCompany("+7-987-654-32-20",
                                                     "password", "Zavod");
        auto id = db::CompanyAPI::createEmployee(company, "Vasya");

        db::CompanyAPI::changeEmployeeFullName(id, "Petya");
        auto b = db::CompanyAPI::getEmployeeById(id);
        CHECK(id == b.id);
        CHECK(b.fullName == "Petya");
        CHECK(company == b.companyId);
    }
}

TEST_CASE("Booking and cancelling") {
    auto company =
        db::CompanyAPI::createCompany("+7-987-654-32-21", "password", "Zavod");
    auto employee = db::CompanyAPI::createEmployee(company, "Petya");
    auto client = db::ClientAPI::createClient("+7-987-654-32-22", "password",
                                              "Vasya", "vasya@mail.com");
    ;
    auto id =
        db::CompanyAPI::createOrder(company, "nogotochki", 1, 2, employee);
    auto a = db::CompanyAPI::getOrderById(id);
    CHECK(isIn(db::CompanyAPI::listVacantOrdersOfCompany(company), id));
    CHECK(isIn(db::CompanyAPI::listVacantOrdersOfEmployee(employee), id));
    CHECK(!isIn(db::CompanyAPI::listBookedOrdersOfCompany(company), id));
    CHECK(!isIn(db::CompanyAPI::listBookedOrdersOfEmployee(employee), id));
    CHECK(!isIn(db::ClientAPI::listOrdersOfClient(client), id));
    CHECK(a.companyId == company);
    CHECK(a.employeeId == employee);
    CHECK(a.clientId == -1);

    db::ClientAPI::bookOrder(a.id, client);
    auto b = db::ClientAPI::getOrderById(a.id);
    CHECK(!isIn(db::CompanyAPI::listVacantOrdersOfCompany(company), a.id));
    CHECK(!isIn(db::CompanyAPI::listVacantOrdersOfEmployee(employee), a.id));
    CHECK(isIn(db::CompanyAPI::listBookedOrdersOfCompany(company), a.id));
    CHECK(isIn(db::CompanyAPI::listBookedOrdersOfEmployee(employee), a.id));
    CHECK(isIn(db::ClientAPI::listOrdersOfClient(client), a.id));
    CHECK(b.companyId == company);
    CHECK(b.employeeId == employee);
    CHECK(b.clientId == client);

    db::ClientAPI::cancelOrder(a.id);
    auto c = db::ClientAPI::getOrderById(a.id);
    CHECK(isIn(db::CompanyAPI::listVacantOrdersOfCompany(company), a.id));
    CHECK(isIn(db::CompanyAPI::listVacantOrdersOfEmployee(employee), a.id));
    CHECK(!isIn(db::CompanyAPI::listBookedOrdersOfCompany(company), a.id));
    CHECK(!isIn(db::CompanyAPI::listBookedOrdersOfEmployee(employee), a.id));
    CHECK(!isIn(db::ClientAPI::listOrdersOfClient(client), a.id));
    CHECK(c.companyId == company);
    CHECK(c.employeeId == employee);
    CHECK(c.clientId == -1);
}
