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
        auto id = db::ClientAPI::createClient("+7-987-654-32-10", "clmPassword",
                                              "Vasya", "vasya@mail.com");
        CHECK(db::ClientAPI::listOrdersOfClient(id).empty());

        auto b = db::ClientAPI::getClient(id);
        CHECK("Vasya" == b.fullName);
        CHECK("vasya@mail.com" == b.email);
        CHECK("+7-987-654-32-10" == b.phoneNumber);
    }

    SUBCASE("Company") {
        auto id = db::CompanyAPI::createCompany("+7-987-654-32-11", "clmPassword",
                                                "Tuturu");

        auto b = db::CompanyAPI::getCompany(id);
        CHECK(isIn(db::ClientAPI::listCompanies(), b.id));
        CHECK("Tuturu" == b.name);
    }

    SUBCASE("Employee") {
        auto company = db::CompanyAPI::createCompany("+7-987-654-32-12",
                                                     "clmPassword", "Zavod");
        auto id = db::CompanyAPI::createEmployee(company, "Vasya");
        CHECK(isIn(db::CompanyAPI::listEmployeesOfCompany(company), id));

        auto b = db::CompanyAPI::getEmployeeById(company, id);
        CHECK(id == b.id);
        CHECK("Vasya" == b.fullName);
    }

    SUBCASE("Order") {
        auto company = db::CompanyAPI::createCompany("+7-987-654-32-13",
                                                     "clmPassword", "Zavod");
        auto employee = db::CompanyAPI::createEmployee(company, "Vasya");
        auto id =
            db::CompanyAPI::createOrder(company, "nogotochki", 1, 2, employee);
        CHECK(isIn(db::CompanyAPI::listVacantOrdersOfCompany(company), id));
        CHECK(isIn(
            db::CompanyAPI::listVacantOrdersOfEmployee(company, employee), id));

        auto b = db::CompanyAPI::getOrderById(company, id);
        CHECK(id == b.id);
        CHECK("nogotochki" == b.title);
        CHECK(1 == b.timeStart);
        CHECK(2 == b.duration);
        CHECK(employee == b.employeeId);
        CHECK(-1 == b.clientId);

        auto c = db::CompanyAPI::createOrder(company, "1234", 1, 2, employee);
        auto d = db::CompanyAPI::createOrder(company, "1234", 1, 2, employee);
        CHECK(isIn(db::CompanyAPI::listVacantOrdersOfCompany(company), c));
        CHECK(isIn(
            db::CompanyAPI::listVacantOrdersOfEmployee(company, employee), c));
        CHECK(isIn(db::CompanyAPI::listVacantOrdersOfCompany(company), d));
        CHECK(isIn(
            db::CompanyAPI::listVacantOrdersOfEmployee(company, employee), d));
    }
}

TEST_CASE("Change structures") {
    SUBCASE("Client email") {
        auto id = db::ClientAPI::createClient("+7-987-654-32-14", "clmPassword",
                                              "Vasya", "vasya@mail.com");

        db::ClientAPI::changeClientEmail(id, "petya@mail.com");
        auto b = db::ClientAPI::getClient(id);
        CHECK("Vasya" == b.fullName);
        CHECK(b.email == "petya@mail.com");
        CHECK("+7-987-654-32-14" == b.phoneNumber);
    }

    SUBCASE("Client fullName") {
        auto id = db::ClientAPI::createClient("+7-987-654-32-15", "clmPassword",
                                              "Vasya", "vasya@mail.com");

        db::ClientAPI::changeClientFullName(id, "Petya");
        auto b = db::ClientAPI::getClient(id);
        CHECK(b.fullName == "Petya");
        CHECK("vasya@mail.com" == b.email);
        CHECK("+7-987-654-32-15" == b.phoneNumber);
    }

    SUBCASE("Order title") {
        auto company = db::CompanyAPI::createCompany("+7-987-654-32-17",
                                                     "clmPassword", "Zavod");
        auto employee = db::CompanyAPI::createEmployee(company, "Vasya");
        auto id =
            db::CompanyAPI::createOrder(company, "nogotochki", 1, 2, employee);

        db::CompanyAPI::changeOrderTitle(company, id, "-____-");
        auto b = db::CompanyAPI::getOrderById(company, id);
        CHECK(id == b.id);
        CHECK(b.title == "-____-");
        CHECK(1 == b.timeStart);
        CHECK(2 == b.duration);
        CHECK(employee == b.employeeId);
        CHECK(-1 == b.clientId);
    }

    SUBCASE("Order timeStart") {
        auto company = db::CompanyAPI::createCompany("+7-987-654-32-18",
                                                     "clmPassword", "Zavod");
        auto employee = db::CompanyAPI::createEmployee(company, "Vasya");
        auto id =
            db::CompanyAPI::createOrder(company, "nogotochki", 1, 2, employee);

        auto newValue = 3;
        db::CompanyAPI::changeOrderTimeStart(company, id, newValue);
        auto b = db::CompanyAPI::getOrderById(company, id);
        CHECK(id == b.id);
        CHECK("nogotochki" == b.title);
        CHECK(b.timeStart == newValue);
        CHECK(2 == b.duration);
        CHECK(employee == b.employeeId);
        CHECK(-1 == b.clientId);
    }

    SUBCASE("Order duration") {
        auto company = db::CompanyAPI::createCompany("+7-987-654-32-19",
                                                     "clmPassword", "Zavod");
        auto employee = db::CompanyAPI::createEmployee(company, "Vasya");
        auto id =
            db::CompanyAPI::createOrder(company, "nogotochki", 1, 2, employee);

        auto newValue = 3;
        db::CompanyAPI::changeOrderDuration(company, id, newValue);
        auto b = db::CompanyAPI::getOrderById(company, id);
        CHECK(id == b.id);
        CHECK("nogotochki" == b.title);
        CHECK(b.timeStart == 1);
        CHECK(newValue == b.duration);
        CHECK(employee == b.employeeId);
        CHECK(-1 == b.clientId);
    }

    SUBCASE("Employee fullName") {
        auto company = db::CompanyAPI::createCompany("+7-987-654-32-20",
                                                     "clmPassword", "Zavod");
        auto id = db::CompanyAPI::createEmployee(company, "Vasya");

        db::CompanyAPI::changeEmployeeFullName(company, id, "Petya");
        auto b = db::CompanyAPI::getEmployeeById(company, id);
        CHECK(id == b.id);
        CHECK(b.fullName == "Petya");
    }
}

TEST_CASE("Booking and cancelling") {
    auto company =
        db::CompanyAPI::createCompany("+7-987-654-32-21", "clmPassword", "Zavod");
    auto employee = db::CompanyAPI::createEmployee(company, "Petya");
    auto client = db::ClientAPI::createClient("+7-987-654-32-22", "clmPassword",
                                              "Vasya", "vasya@mail.com");
    auto id =
        db::CompanyAPI::createOrder(company, "nogotochki", 1, 2, employee);
    auto a = db::CompanyAPI::getOrderById(company, id);
    CHECK(isIn(db::CompanyAPI::listVacantOrdersOfCompany(company), id));
    CHECK(isIn(db::CompanyAPI::listVacantOrdersOfEmployee(company, employee),
               id));
    CHECK(!isIn(db::CompanyAPI::listBookedOrdersOfCompany(company), id));
    CHECK(!isIn(db::CompanyAPI::listBookedOrdersOfEmployee(company, employee),
                id));
    CHECK(!isIn(db::ClientAPI::listOrdersOfClient(client), id));
    CHECK(a.employeeId == employee);
    CHECK(a.clientId == -1);

    db::ClientAPI::bookOrder(client, a.id);
    auto b = db::ClientAPI::getOrderById(client, a.id);
    CHECK(!isIn(db::CompanyAPI::listVacantOrdersOfCompany(company), a.id));
    CHECK(!isIn(db::CompanyAPI::listVacantOrdersOfEmployee(company, employee),
                a.id));
    CHECK(isIn(db::CompanyAPI::listBookedOrdersOfCompany(company), a.id));
    CHECK(isIn(db::CompanyAPI::listBookedOrdersOfEmployee(company, employee),
               a.id));
    CHECK(isIn(db::ClientAPI::listOrdersOfClient(client), a.id));
    CHECK(b.employeeId == employee);

    db::ClientAPI::cancelOrder(client, a.id);
    auto c = db::ClientAPI::getOrderById(client, a.id);
    CHECK(isIn(db::CompanyAPI::listVacantOrdersOfCompany(company), a.id));
    CHECK(isIn(db::CompanyAPI::listVacantOrdersOfEmployee(company, employee),
               a.id));
    CHECK(!isIn(db::CompanyAPI::listBookedOrdersOfCompany(company), a.id));
    CHECK(!isIn(db::CompanyAPI::listBookedOrdersOfEmployee(company, employee),
                a.id));
    CHECK(!isIn(db::ClientAPI::listOrdersOfClient(client), a.id));
    CHECK(c.employeeId == employee);
    CHECK(c.clientId == -1);
}
