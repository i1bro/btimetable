#pragma comment(lib, "ws2_32.lib")

#include "btt/Service.h"
#include "CompanyAPI.h"
#include "ClientAPI.h"
#include "Entities.h"
#include "doctest.h"
#include "sw/redis++/redis++.h"

sw::redis::Redis redis = sw::redis::Redis("tcp://retired.tk:58973");

TEST_CASE ("Create structures") {
    redis.flushall();

    SUBCASE("Client") {
        auto a = dataBase::ClientAPI::createClient("Vasya",
                                                   "+7-987-654-32-10",
                                                   "vasya@mail.com");
        CHECK(dataBase::ClientAPI::listOrdersOfClient(a.id).empty());

        auto b = dataBase::ClientAPI::getClientById(a.id);
        CHECK(a.id == b.id);
        CHECK(a.fullName == b.fullName);
        CHECK(a.email == b.email);
        CHECK(a.phoneNumber == b.phoneNumber);
    }

    SUBCASE("Company") {
        auto a = dataBase::CompanyAPI::createCompany("Tuturu");
        CHECK(dataBase::ClientAPI::listCompanies().front() == a.id);

        auto b = dataBase::CompanyAPI::getCompanyById(a.id);
        CHECK(a.id == b.id);
        CHECK(a.name == b.name);
    }

    SUBCASE("Employee") {
        auto company = dataBase::CompanyAPI::createCompany("Zavod");
        auto a = dataBase::CompanyAPI::createEmployee(company.id, "Vasya");
        CHECK(dataBase::CompanyAPI::listEmployeesOfCompany(company.id).front() == a.id);

        auto b = dataBase::CompanyAPI::getEmployeeById(a.id);
        CHECK(a.id == b.id);
        CHECK(a.fullName == b.fullName);
        CHECK(a.companyId == b.companyId);
    }

    SUBCASE("Order") {
        auto company = dataBase::CompanyAPI::createCompany("Zavod");
        auto employee = dataBase::CompanyAPI::createEmployee(company.id, "Vasya");
        auto a = dataBase::CompanyAPI::createOrder(company.id, "nogotochki", 1, 2, employee.id);
        CHECK(dataBase::CompanyAPI::listVacantOrdersOfCompany(company.id).front() == a.id);
        CHECK(dataBase::CompanyAPI::listVacantOrdersOfEmployee(employee.id).front() == a.id);

        auto b = dataBase::CompanyAPI::getOrderById(a.id);
        CHECK(a.id == b.id);
        CHECK(a.title == b.title);
        CHECK(a.companyId == b.companyId);
        CHECK(a.timeStart == b.timeStart);
        CHECK(a.duration == b.duration);
        CHECK(a.employeeId == b.employeeId);
    }
}


