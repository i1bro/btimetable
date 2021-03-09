#include "Entities.h"

namespace dataBase {

void Schedule::addVacantOrder(long long id) {
    vacantOrders.push_back(id);
}

void Schedule::addBookedOrder(long long id) {
    bookedOrders.push_back(id);
}

const std::vector<long long> &Schedule::listVacantOrders() const {
    return vacantOrders;
}

const std::vector<long long> &Schedule::listBookedOrders() const {
    return bookedOrders;
}

void Schedule::deleteOrder(long long id) {
    for (std::size_t i = 0; i < vacantOrders.size(); i++) {
        if (vacantOrders[i] == id) {
            vacantOrders.erase(vacantOrders.begin() + i);
            break;
        }
    }
    for (std::size_t i = 0; i < bookedOrders.size(); i++) {
        if (bookedOrders[i] == id) {
            bookedOrders.erase(bookedOrders.begin() + i);
            break;
        }
    }
}

void Company::addEmployee(long long id) {
    employees.push_back(id);
}

const std::vector<long long> &Company::listEmployees() const {
    return employees;
}

void Company::deleteEmployee(long long id) {
    for (std::size_t i = 0; i < employees.size(); i++) {
        if (employees[i] == id) {
            employees.erase(employees.begin() + i);
            break;
        }
    }
}

void Company::addVacantOrder(long long id) {
    schedule.addVacantOrder(id);
}

void Company::addBookedOrder(long long id) {
    schedule.addBookedOrder(id);
}

const std::vector<long long> &Company::listVacantOrders() const {
    return schedule.listVacantOrders();
}

const std::vector<long long> &Company::listBookedOrders() const {
    return schedule.listBookedOrders();
}

void Company::deleteOrder(long long id) {
    schedule.deleteOrder(id);
}

const Schedule &Company::getSchedule() const {
    return schedule;
}
}  // namespace dataBase