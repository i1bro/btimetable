#include "btt/Service.h"
#include <jwt-cpp/jwt.h>
#include <iostream>

namespace db {

long long Service::createCompany(const std::string &phoneNumber,
                                 const std::string &password,
                                 const std::string &name) {
    long long resId =
        storage
            .execute(
                Insert(companies).set(Column::name, name).returning(Column::id))
            .toLL();
    storage.execute(Insert(companyAccounts)
                        .set(Column::phoneNumber, phoneNumber)
                        .set(Column::password, password)
                        .set(Column::companyId, resId));
    return resId;
}

long long Service::createOrder(long long companyId,
                               const std::string &title,
                               long long timeStart,
                               long long duration,
                               long long employeeId) {
    long long resId = storage
                          .execute(Insert(orders)
                                       .set(Column::companyId, companyId)
                                       .set(Column::title, title)
                                       .set(Column::timeStart, timeStart)
                                       .set(Column::duration, duration)
                                       .set(Column::employeeId, employeeId)
                                       .returning(Column::id))
                          .toLL();
    return resId;
}

long long Service::createEmployee(long long companyId,
                                  const std::string &fullName) {
    long long resId = storage
                          .execute(Insert(employees)
                                       .set(Column::companyId, companyId)
                                       .set(Column::fullName, fullName)
                                       .returning(Column::id))
                          .toLL();
    return resId;
}

long long Service::createClient(const std::string &phoneNumber,
                                const std::string &password,
                                const std::string &fullName,
                                const std::string &email) {
    long long resId = storage
                          .execute(Insert(clients)
                                       .set(Column::fullName, fullName)
                                       .set(Column::phoneNumber, phoneNumber)
                                       .set(Column::email, email)
                                       .returning(Column::id))
                          .toLL();
    storage.execute(Insert(clientAccounts)
                        .set(Column::phoneNumber, phoneNumber)
                        .set(Column::password, password)
                        .set(Column::clientId, resId));
    return resId;
}

std::vector<long long> Service::listVacantOrdersOfCompany(long long id) {
    return storage
        .execute(Select(orders)
                     .columns({Column::id})
                     .where(companyId, id)
                     .where(status, Order::vacant))
        .toVecLL();
}

std::vector<long long> Service::listBookedOrdersOfCompany(long long id) {
    return storage
        .execute(Select(orders)
                     .columns({Column::id})
                     .where(companyId, id)
                     .where(status, Order::booked))
        .toVecLL();
}

std::vector<long long> Service::listAllOrdersOfCompany(long long id) {
    return storage
        .execute(Select(orders)
                     .columns({Column::id})
                     .where(companyId, id)
                     .where(status, Order::deleted, "!="))
        .toVecLL();
}

Order Service::getOrderById(long long id) {
    return storage.execute(Select(orders).columns({all}).where(Column::id, id))
        .toOrder();
}

Employee Service::getEmployeeById(long long id) {
    return storage
        .execute(Select(employees).columns({all}).where(Column::id, id))
        .toEmployee();
}

Client Service::getClientById(long long id) {
    return storage.execute(Select(clients).columns({all}).where(Column::id, id))
        .toClient();
}

Company Service::getCompanyById(long long id) {
    return storage
        .execute(Select(companies).columns({all}).where(Column::id, id))
        .toCompany();
}

void Service::saveOrder(const Order &order) {
    storage.execute(Update(orders)
                        .set(title, order.title)
                        .set(timeStart, order.timeStart)
                        .set(duration, order.duration)
                        .set(employeeId, order.employeeId)
                        .where(id, order.id));
    if (order.clientId == -1) {
        storage.execute(Update(orders).setNull(clientId).where(id, order.id));
    } else {
        storage.execute(
            Update(orders).set(clientId, order.clientId).where(id, order.id));
    }
}

void Service::saveEmployee(const Employee &employee) {
    storage.execute(Update(employees)
                        .set(fullName, employee.fullName)
                        .where(id, employee.id));
}

void Service::saveClient(const Client &client) {
    storage.execute(Update(clients)
                        .set(fullName, client.fullName)
                        .set(phoneNumber, client.phoneNumber)
                        .set(email, client.email)
                        .where(id, client.id));
}

void Service::saveCompany(const Company &company) {
    storage.execute(
        Update(companies).set(name, company.name).where(id, company.id));
}

std::vector<long long> Service::listVacantOrdersOfEmployee(long long id) {
    return storage
        .execute(Select(orders)
                     .columns({Column::id})
                     .where(employeeId, id)
                     .where(status, Order::vacant))
        .toVecLL();
}

std::vector<long long> Service::listBookedOrdersOfEmployee(long long id) {
    return storage
        .execute(Select(orders)
                     .columns({Column::id})
                     .where(employeeId, id)
                     .where(status, Order::booked))
        .toVecLL();
}

std::vector<long long> Service::listAllOrdersOfEmployee(long long id) {
    return storage
        .execute(Select(orders)
                     .columns({Column::id})
                     .where(employeeId, id)
                     .where(status, Order::deleted, "!="))
        .toVecLL();
}

std::vector<long long> Service::listOrdersOfClient(long long id) {
    return storage
        .execute(Select(orders)
                     .columns({Column::id})
                     .where(clientId, id)
                     .where(status, Order::deleted, "!="))
        .toVecLL();
}

std::vector<long long> Service::listCompanies() {
    return storage.execute(Select(companies).columns({id})).toVecLL();
}

std::vector<long long> Service::listEmployeesOfCompany(long long id) {
    return storage
        .execute(Select(employees).columns({Column::id}).where(companyId, id))
        .toVecLL();
}

void Service::deleteOrder(long long id) {
    storage.execute(
        Update(orders).set(status, Order::deleted).where(Column::id, id));
}

void Service::bookOrder(long long orderId, long long clientId) {
    storage.execute(Update(orders)
                        .set(Column::clientId, clientId)
                        .set(status, Order::booked)
                        .where(Column::id, orderId));
}

void Service::cancelOrder(long long id) {
    storage.execute(Update(orders)
                        .setNull(Column::clientId)
                        .set(status, Order::vacant)
                        .where(Column::id, id));
}

void Service::rateOrder(long long id, int rating) {
    if (1 > rating || rating > 5) {
        throw std::exception();  // TODO
    }
    auto order = getOrderById(id);
    long long curCompanyRatingSum =
        storage
            .execute(Select(companies)
                         .columns({Column::ratingSum})
                         .where(Column::id, order.companyId))
            .toLL();
    long long curEmployeeRatingSum =
        storage
            .execute(Select(employees)
                         .columns({Column::ratingSum})
                         .where(Column::id, order.employeeId))
            .toLL();
    storage.execute(
        Update(companies)
            .set(Column::ratingSum, curCompanyRatingSum + rating - order.rating)
            .where(Column::id, order.companyId));
    storage.execute(Update(employees)
                        .set(Column::ratingSum,
                             curEmployeeRatingSum + rating - order.rating)
                        .where(Column::id, order.employeeId));
    if (order.rating == 0) {
        long long curCompanyRatingCnt =
            storage
                .execute(Select(companies)
                             .columns({Column::ratingCnt})
                             .where(Column::id, order.companyId))
                .toLL();
        long long curEmployeeRatingCnt =
            storage
                .execute(Select(employees)
                             .columns({Column::ratingCnt})
                             .where(Column::id, order.employeeId))
                .toLL();
        storage.execute(Update(companies)
                            .set(Column::ratingCnt, curCompanyRatingCnt + 1)
                            .where(Column::id, order.companyId));
        storage.execute(Update(employees)
                            .set(Column::ratingCnt, curEmployeeRatingCnt + 1)
                            .where(Column::id, order.employeeId));
    }
    storage.execute(
        Update(orders).set(Column::rating, rating).where(Column::id, id));
}

long long Service::authorizeClient(const std::string &phoneNumber,
                                   const std::string &password) {
    auto res = storage.execute(Select(clientAccounts)
                                   .columns({clientId})
                                   .where(Column::phoneNumber, phoneNumber)
                                   .where(Column::password, password));
    try {
        return res.toLL();
    } catch (...) {
        throw std::exception();  // TODO
    }
}

long long Service::authorizeCompany(const std::string &phoneNumber,
                                    const std::string &password) {
    auto res = storage.execute(Select(companyAccounts)
                                   .columns({companyId})
                                   .where(Column::phoneNumber, phoneNumber)
                                   .where(Column::password, password));
    try {
        return res.toLL();
    } catch (...) {
        throw std::exception();  // TODO
    }
}

std::vector<long long> Service::listOrders(long long companyId,
                                           long long employeeId,
                                           Order::statusEnum status,
                                           long long leastTimeStart,
                                           long long leastDuration,
                                           sortParam sortBy,
                                           bool reversed) {
    auto query = Select(orders)
                     .columns({id})
                     .where(Column::status, status)
                     .where(Column::duration, leastDuration, ">")
                     .where(Column::timeStart, leastTimeStart, ">");
    if (companyId != -1) {
        query.where(Column::companyId, companyId);
    }
    if (employeeId != -1) {
        query.where(Column::employeeId, employeeId);
    }
    switch (sortBy) {
        case byId:
            query.orderedBy(id, reversed);
            break;
        case byTimeStart:
            query.orderedBy(timeStart, reversed);
            break;
        case byDuration:
            query.orderedBy(duration, reversed);
            break;
        default:
            throw std::exception();  // TODO
    }
    return storage.execute(query).toVecLL();
}

namespace {
const std::string &rsaPrivKey() {
    static const std::string s = R"(-----BEGIN RSA PRIVATE KEY-----
MIICXQIBAAKBgQDJ1qk4Ksd6BjIntQKzCUP+1fVj2TkoglyPY3I6nWfqn+oUnk1e
m2BDtdl1og8TlwtfQJFUePG48WHdVylBw8MowDWKp4e+fyciO1y4RxJRYsTfcOhR
GYDTLjm/Kpa0bjMMOXl6AJijD8bvooAQbSlcxbmBZecXTmDuafIZ/KGGtwIDAQAB
AoGAXxjStfIB9k5BB1BTq0MsVD8+1QKd2aZCMhTq1w8ezP73bSuAzJhsbLqbcL8g
V1yNMR3c2234hejE8WKFv8SaiBwvD7iSgG4oP9eBdfzeF38PvhR96/G02sKy67OS
BTrypvYh0g3TF8Ylucvs9Jx0Klsoz1rlzHS1WZBIxnyC23ECQQDwVgPxoZeZNPVy
/I40Id++M+8IWHlNpbE1u7mJpae8Gr89EA4NC7POzMc+yAWB4GINDKgNPnpmmxoC
u2vVnja1AkEA1v5RkfteKJS45b8/B7aFqeDm0ozST5rkfZf8MJakKJph57p0EAcg
SpC72cWrCKktiEfyb7a6oa9Tld7s2j8fOwJBALS3+T84w0XxDJ/qSQPqdNQROSyN
WqmIbjh5cIqQhhBsDGFeMTKeGhbm5OvQfFOs5g3p9nP/Bwsgle54AB4hWgECQQCu
6mrjImgRDC8CfP6C//TvqZMiaoARVCviIu2DeoxEnJZbOk+DWsji4a50F2Z3vWzW
G/MbAMgHE+YlYSHCzuhRAkBMYUBIZuWgE5LgVkuEPvkvA92rIiFQEfrAdMQ/y7K/
vbJRFIhMT44Aa/HL6NYo2GfaV1dWw6JTphZonwbiQ9bF
-----END RSA PRIVATE KEY-----)";
    return s;
}
const std::string &rsaPubKey() {
    static const std::string s = R"(-----BEGIN PUBLIC KEY-----
MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDJ1qk4Ksd6BjIntQKzCUP+1fVj
2TkoglyPY3I6nWfqn+oUnk1em2BDtdl1og8TlwtfQJFUePG48WHdVylBw8MowDWK
p4e+fyciO1y4RxJRYsTfcOhRGYDTLjm/Kpa0bjMMOXl6AJijD8bvooAQbSlcxbmB
ZecXTmDuafIZ/KGGtwIDAQAB
-----END PUBLIC KEY-----)";
    return s;
}
}  // namespace

std::string Service::createToken(long long id, const std::string &role) {
    auto token =
        jwt::create()
            .set_issuer("server")
            .set_type("JWT")
            .set_payload_claim("id",
                               jwt::claim(std::string{std::to_string(id)}))
            .set_payload_claim("role", jwt::claim(std::string{role}))
            .sign(jwt::algorithm::rs256(rsaPubKey(), rsaPrivKey(), "", ""));

    return token;
}

std::pair<long long, std::string> Service::verifyToken(
    const std::string &token) {
    auto verify = jwt::verify()
                      .allow_algorithm(jwt::algorithm::rs256(
                          rsaPubKey(), rsaPrivKey(), "", ""))
                      .with_issuer("server");

    auto decoded = jwt::decode(token);

    verify.verify(decoded);

    return {std::stoll(decoded.get_payload_claims()["id"].to_json().to_str()),
            decoded.get_payload_claims()["role"].to_json().to_str()};
}

}  // namespace db
