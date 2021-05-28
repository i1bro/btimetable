#include "btt/Service.h"
#include <jwt-cpp/jwt.h>
#include <string>
#include <vector>

namespace db {

namespace {
struct bttExecutionError : bttError {
    explicit bttExecutionError()
        : bttError(
              "An unexpected error occurred while running this operation.") {
    }
};

struct bttSortParamError : bttError {
    explicit bttSortParamError() : bttError("Invalid sort parameter.") {
    }
};

struct bttInvalidRatingError : bttError {
    explicit bttInvalidRatingError()
        : bttError("Rating must be a number from 1 to 5.") {
    }
};

struct bttLoginError : bttError {
    explicit bttLoginError() : bttError("Incorrect phone number or password.") {
    }
};

struct bttRegistrationError : bttError {
    explicit bttRegistrationError()
        : bttError("Account with this phone number already exists.") {
    }
};

struct bttTokenCreationError : bttFatalError {
    explicit bttTokenCreationError()
        : bttFatalError("Could not create authorisation token.") {
    }
};

struct bttInvalidTokenError : bttError {
    explicit bttInvalidTokenError()
        : bttError(
              "Invalid authorisation token. Try logging in again or restarting "
              "the app.") {
    }
};
}  // namespace

Storage &Service::storage() {
    try {
        static Storage storage_ = Storage();
        return storage_;
    } catch (...) {
        throw bttFatalError("Can't connect to data base.");
    }
}

long long Service::createCompany(const std::string &phoneNumber,
                                 const std::string &password,
                                 const std::string &name) {
    try {
        auto work = storage().startWork();
        long long resId =
            storage()
                .execute(
                    work,
                    Insert(tblCompanies).set(clmName, name).returning(clmId))
                .toLL();
        if (!storage()
                 .execute(work, Select(tblCompanyAccounts)
                                    .columns({clmCompanyId})
                                    .where(clmPhoneNumber, phoneNumber))
                 .toVecLL()
                 .empty()) {
            throw bttRegistrationError();
        }
        storage().execute(work, Insert(tblCompanyAccounts)
                                    .set(clmPhoneNumber, phoneNumber)
                                    .set(clmPassword, password)
                                    .set(clmCompanyId, resId));
        work.commit();
        return resId;
    } catch (processingQueryError &) {
        throw bttExecutionError();
    }
}

long long Service::createOrder(long long companyId,
                               const std::string &title,
                               long long timeStart,
                               long long duration,
                               long long employeeId) {
    try {
        long long resId = storage()
                              .execute(Insert(tblOrders)
                                           .set(clmCompanyId, companyId)
                                           .set(clmTitle, title)
                                           .set(clmTimeStart, timeStart)
                                           .set(clmDuration, duration)
                                           .set(clmEmployeeId, employeeId)
                                           .returning(clmId))
                              .toLL();
        return resId;
    } catch (processingQueryError &) {
        throw bttExecutionError();
    }
}

long long Service::createEmployee(long long companyId,
                                  const std::string &fullName) {
    try {
        long long resId = storage()
                              .execute(Insert(tblEmployees)
                                           .set(clmCompanyId, companyId)
                                           .set(clmFullName, fullName)
                                           .returning(clmId))
                              .toLL();
        return resId;
    } catch (processingQueryError &) {
        throw bttExecutionError();
    }
}

long long Service::createClient(const std::string &phoneNumber,
                                const std::string &password,
                                const std::string &fullName,
                                const std::string &email) {
    try {
        auto work = storage().startWork();
        long long resId =
            storage()
                .execute(work, Insert(tblClients)
                                   .set(clmFullName, fullName)
                                   .set(clmPhoneNumber, phoneNumber)
                                   .set(clmEmail, email)
                                   .returning(clmId))
                .toLL();
        if (!storage()
                 .execute(work, Select(tblClientAccounts)
                                    .columns({clmClientId})
                                    .where(clmPhoneNumber, phoneNumber))
                 .toVecLL()
                 .empty()) {
            throw bttRegistrationError();
        }
        storage().execute(work, Insert(tblClientAccounts)
                                    .set(clmPhoneNumber, phoneNumber)
                                    .set(clmPassword, password)
                                    .set(clmClientId, resId));
        work.commit();
        return resId;
    } catch (processingQueryError &) {
        throw bttExecutionError();
    }
}

std::vector<long long> Service::listVacantOrdersOfCompany(long long id) {
    try {
        return storage()
            .execute(
                Select(tblOrders)
                    .columns({clmId})
                    .where(clmCompanyId, id)
                    .where(clmStatus, static_cast<long long>(Order::vacant)))
            .toVecLL();
    } catch (processingQueryError &) {
        throw bttExecutionError();
    }
}

std::vector<long long> Service::listBookedOrdersOfCompany(long long id) {
    try {
        return storage()
            .execute(
                Select(tblOrders)
                    .columns({clmId})
                    .where(clmCompanyId, id)
                    .where(clmStatus, static_cast<long long>(Order::booked)))
            .toVecLL();
    } catch (processingQueryError &) {
        throw bttExecutionError();
    }
}

std::vector<long long> Service::listAllOrdersOfCompany(long long id) {
    try {
        return storage()
            .execute(Select(tblOrders)
                         .columns({clmId})
                         .where(clmCompanyId, id)
                         .where(clmStatus, Order::deleted, "!="))
            .toVecLL();
    } catch (processingQueryError &) {
        throw bttExecutionError();
    }
}

Order Service::getOrderById(long long id) {
    try {
        return storage()
            .execute(Select(tblOrders).columns({clmAll}).where(clmId, id))
            .toOrder();
    } catch (processingQueryError &) {
        throw bttExecutionError();
    }
}

Employee Service::getEmployeeById(long long id) {
    try {
        return storage()
            .execute(Select(tblEmployees).columns({clmAll}).where(clmId, id))
            .toEmployee();
    } catch (processingQueryError &) {
        throw bttExecutionError();
    }
}

Client Service::getClientById(long long id) {
    try {
        return storage()
            .execute(Select(tblClients).columns({clmAll}).where(clmId, id))
            .toClient();
    } catch (processingQueryError &) {
        throw bttExecutionError();
    }
}

Company Service::getCompanyById(long long id) {
    try {
        return storage()
            .execute(Select(tblCompanies).columns({clmAll}).where(clmId, id))
            .toCompany();
    } catch (processingQueryError &) {
        throw bttExecutionError();
    }
}

void Service::saveOrder(const Order &order) {
    try {
        auto work = storage().startWork();
        storage().execute(work, Update(tblOrders)
                                    .set(clmTitle, order.title)
                                    .set(clmTimeStart, order.timeStart)
                                    .set(clmDuration, order.duration)
                                    .set(clmEmployeeId, order.employeeId)
                                    .where(clmId, order.id));
        if (order.clientId == -1) {
            storage().execute(
                work,
                Update(tblOrders).setNull(clmClientId).where(clmId, order.id));
        } else {
            storage().execute(work, Update(tblOrders)
                                        .set(clmClientId, order.clientId)
                                        .where(clmId, order.id));
        }
        work.commit();
    } catch (processingQueryError &) {
        throw bttExecutionError();
    }
}

void Service::saveEmployee(const Employee &employee) {
    try {
        storage().execute(Update(tblEmployees)
                              .set(clmFullName, employee.fullName)
                              .where(clmId, employee.id));
    } catch (processingQueryError &) {
        throw bttExecutionError();
    }
}

void Service::saveClient(const Client &client) {
    try {
        storage().execute(Update(tblClients)
                              .set(clmFullName, client.fullName)
                              .set(clmPhoneNumber, client.phoneNumber)
                              .set(clmEmail, client.email)
                              .where(clmId, client.id));
    } catch (processingQueryError &) {
        throw bttExecutionError();
    }
}

void Service::saveCompany(const Company &company) {
    try {
        storage().execute(Update(tblCompanies)
                              .set(clmName, company.name)
                              .where(clmId, company.id));
    } catch (processingQueryError &) {
        throw bttExecutionError();
    }
}

std::vector<long long> Service::listVacantOrdersOfEmployee(long long id) {
    try {
        return storage()
            .execute(
                Select(tblOrders)
                    .columns({clmId})
                    .where(clmEmployeeId, id)
                    .where(clmStatus, static_cast<long long>(Order::vacant)))
            .toVecLL();
    } catch (processingQueryError &) {
        throw bttExecutionError();
    }
}

std::vector<long long> Service::listBookedOrdersOfEmployee(long long id) {
    try {
        return storage()
            .execute(
                Select(tblOrders)
                    .columns({clmId})
                    .where(clmEmployeeId, id)
                    .where(clmStatus, static_cast<long long>(Order::booked)))
            .toVecLL();
    } catch (processingQueryError &) {
        throw bttExecutionError();
    }
}

std::vector<long long> Service::listAllOrdersOfEmployee(long long id) {
    try {
        return storage()
            .execute(Select(tblOrders)
                         .columns({clmId})
                         .where(clmEmployeeId, id)
                         .where(clmStatus, Order::deleted, "!="))
            .toVecLL();
    } catch (processingQueryError &) {
        throw bttExecutionError();
    }
}

std::vector<long long> Service::listOrdersOfClient(long long id) {
    try {
        return storage()
            .execute(Select(tblOrders)
                         .columns({clmId})
                         .where(clmClientId, id)
                         .where(clmStatus, Order::deleted, "!="))
            .toVecLL();
    } catch (processingQueryError &) {
        throw bttExecutionError();
    }
}

std::vector<long long> Service::listCompanies(sortParam sorted) {
    try {
        auto query = Select(tblCompanies).columns({clmId});
        switch (sorted) {
            case byName:
                query.orderedBy(clmFullName);
                break;
            case byRating:
                query.orderedBy("rating_sum / GREATEST (rating_cnt, 1) DESC");
                break;
            default:
                throw bttSortParamError();
        }
        return storage().execute(query).toVecLL();
    } catch (processingQueryError &) {
        throw bttExecutionError();
    }
}

std::vector<long long> Service::listEmployeesOfCompany(long long id,
                                                       sortParam sorted) {
    try {
        auto query = Select(tblEmployees)
                         .columns({clmId})
                         .where(clmCompanyId, id)
                         .where(clmIsDeleted, false);
        switch (sorted) {
            case byName:
                query.orderedBy(clmFullName);
                break;
            case byRating:
                query.orderedBy("rating_sum / GREATEST (rating_cnt, 1) DESC");
                break;
            default:
                throw bttSortParamError();
        }
        return storage().execute(query).toVecLL();
    } catch (processingQueryError &) {
        throw bttExecutionError();
    }
}

void Service::deleteEmployee(long long id) {
    try {
        auto work = storage().startWork();
        storage().execute(
            work,
            Update(tblEmployees).set(clmIsDeleted, true).where(clmId, id));
        storage().execute(
            work, Update(tblOrders)
                      .set(clmStatus, static_cast<long long>(Order::deleted))
                      .where(clmEmployeeId, id));
        work.commit();
    } catch (processingQueryError &) {
        throw bttExecutionError();
    }
}

void Service::deleteOrder(long long id) {
    try {
        storage().execute(
            Update(tblOrders)
                .set(clmStatus, static_cast<long long>(Order::deleted))
                .where(clmId, id));
    } catch (processingQueryError &) {
        throw bttExecutionError();
    }
}

void Service::bookOrder(long long orderId, long long clientId) {
    try {
        storage().execute(
            Update(tblOrders)
                .set(clmClientId, clientId)
                .set(clmStatus, static_cast<long long>(Order::booked))
                .where(clmId, orderId));
    } catch (processingQueryError &) {
        throw bttExecutionError();
    }
}

void Service::cancelOrder(long long id) {
    try {
        storage().execute(
            Update(tblOrders)
                .setNull(clmClientId)
                .set(clmStatus, static_cast<long long>(Order::vacant))
                .where(clmId, id));
    } catch (processingQueryError &) {
        throw bttExecutionError();
    }
}

void Service::rateOrder(long long id, int rating) {
    try {
        if (1 > rating || rating > 5) {
            throw bttInvalidRatingError();
        }
        auto order = getOrderById(id);
        auto work = storage().startWork();
        long long curCompanyRatingSum =
            storage()
                .execute(work, Select(tblCompanies)
                                   .columns({clmRatingSum})
                                   .where(clmId, order.companyId))
                .toLL();
        long long curEmployeeRatingSum =
            storage()
                .execute(work, Select(tblEmployees)
                                   .columns({clmRatingSum})
                                   .where(clmId, order.employeeId))
                .toLL();
        storage().execute(
            work,
            Update(tblCompanies)
                .set(clmRatingSum, curCompanyRatingSum + rating - order.rating)
                .where(clmId, order.companyId));
        storage().execute(
            work,
            Update(tblEmployees)
                .set(clmRatingSum, curEmployeeRatingSum + rating - order.rating)
                .where(clmId, order.employeeId));
        if (order.rating == 0) {
            long long curCompanyRatingCnt =
                storage()
                    .execute(work, Select(tblCompanies)
                                       .columns({clmRatingCnt})
                                       .where(clmId, order.companyId))
                    .toLL();
            long long curEmployeeRatingCnt =
                storage()
                    .execute(work, Select(tblEmployees)
                                       .columns({clmRatingCnt})
                                       .where(clmId, order.employeeId))
                    .toLL();
            storage().execute(work,
                              Update(tblCompanies)
                                  .set(clmRatingCnt, curCompanyRatingCnt + 1)
                                  .where(clmId, order.companyId));
            storage().execute(work,
                              Update(tblEmployees)
                                  .set(clmRatingCnt, curEmployeeRatingCnt + 1)
                                  .where(clmId, order.employeeId));
        }
        storage().execute(work,
                          Update(tblOrders)
                              .set(clmRating, static_cast<long long>(rating))
                              .where(clmId, id));
        work.commit();
    } catch (processingQueryError &) {
        throw bttExecutionError();
    }
}

long long Service::authorizeClient(const std::string &phoneNumber,
                                   const std::string &password) {
    try {
        auto res = storage().execute(Select(tblClientAccounts)
                                         .columns({clmClientId})
                                         .where(clmPhoneNumber, phoneNumber)
                                         .where(clmPassword, password));
        try {
            return res.toLL();
        } catch (...) {
            throw bttLoginError();
        }
    } catch (processingQueryError &) {
        throw bttExecutionError();
    }
}

long long Service::authorizeCompany(const std::string &phoneNumber,
                                    const std::string &password) {
    try {
        auto res = storage().execute(Select(tblCompanyAccounts)
                                         .columns({clmCompanyId})
                                         .where(clmPhoneNumber, phoneNumber)
                                         .where(clmPassword, password));
        try {
            return res.toLL();
        } catch (...) {
            throw bttLoginError();
        }
    } catch (processingQueryError &) {
        throw bttExecutionError();
    }
}

std::vector<long long> Service::listOrders(const orderSearchParams &params) {
    try {
        auto query =
            Select(tblOrders)
                .columns({clmId})
                .where(clmStatus, static_cast<long long>(Order::vacant))
                .where(clmDuration, params.minDuration, ">=")
                .where(clmTimeStart, params.minTimeStart, ">=");
        if (params.maxDuration != -1) {
            query.where(clmCompanyId, params.maxDuration, "<=");
        }
        if (params.maxTimeStart != -1) {
            query.where(clmEmployeeId, params.maxTimeStart, "<=");
        }
        if (params.companyId != -1) {
            query.where(clmCompanyId, params.companyId);
        }
        if (params.employeeId != -1) {
            query.where(clmEmployeeId, params.employeeId);
        }
        if (!params.title.empty()) {
            query.where(clmTitle, params.title);
        }
        switch (params.sorted) {
            case byTimeStart:
                query.orderedBy(clmTimeStart);
                break;
            case byDuration:
                query.orderedBy(clmDuration);
                break;
            case byName:
                query.orderedBy(clmTitle);
                break;
            default:
                throw bttSortParamError();
        }
        return storage().execute(query).toVecLL();
    } catch (processingQueryError &) {
        throw bttExecutionError();
    }
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
    try {
        auto token =
            jwt::create()
                .set_issuer("btt")
                .set_type("JWT")
                .set_payload_claim("id",
                                   jwt::claim(std::string{std::to_string(id)}))
                .set_payload_claim("role", jwt::claim(std::string{role}))
                .sign(jwt::algorithm::rs256(rsaPubKey(), rsaPrivKey(), "", ""));

        return token;
    } catch (...) {
        throw bttTokenCreationError();
    }
}

long long Service::verifyToken(const std::string &token,
                               const std::string &role) {
    std::string parsedRole;
    long long parsedId;
    try {
        auto verify = jwt::verify()
                          .allow_algorithm(jwt::algorithm::rs256(
                              rsaPubKey(), rsaPrivKey(), "", ""))
                          .with_issuer("btt");
        auto decoded = jwt::decode(token);
        verify.verify(decoded);
        parsedRole = decoded.get_payload_claims()["role"].to_json().to_str();
        parsedId =
            std::stoll(decoded.get_payload_claims()["id"].to_json().to_str());
    } catch (...) {
        throw bttInvalidTokenError();
    }

    if (parsedRole != role) {
        throw bttInvalidTokenError();
    }
    return parsedId;
}

}  // namespace db
