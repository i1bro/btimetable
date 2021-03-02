#include "Entities.h"

namespace dataBase {

template <typename T>
void Holder<T>::add(T value) {
    auto element = new T(std::move(value));
    std::shared_ptr<T> elementPtr(element);
    elements.push_back(elementPtr);
    idMap[elementPtr->id] = elementPtr;
}

template <typename T>
void Holder<T>::addByPtr(std::shared_ptr<T> elementPtr) {
    elements.push_back(elementPtr);
    idMap[elementPtr->id] = elementPtr;
}

template <typename T>
std::shared_ptr<T> Holder<T>::findById(int id) {
    return idMap[id];
}

template <typename T>
void Holder<T>::removeById(int id) {
    idMap[id].reset();
    for (int ind = 0; ind < static_cast<int>(elements.size()); ind++) {
        if ((elements[ind]->id) == id) {
            elements.erase(elements.begin() + ind);
            return;
        }
    }
}

template <typename T>
const std::vector<std::shared_ptr<T>> &Holder<T>::listElements() {
    return elements;
}

void Company::addEmployee(std::string fullName) {
    employees.add(Employee(++lastEmployeeId, std::move(fullName)));
}

void Company::addClient(std::string fullName) {
    clients.add(Client(++lastClientId, std::move(fullName)));
}

void Company::deleteEmployee(int id) {
    employees.removeById(id);
}

void Company::deleteClient(int id) {
    clients.removeById(id);
}

void Company::addOrder(std::string title,
                       int timeStart,
                       int duration,
                       int employeeId) {
    schedule.addOrder(++lastOrderId, std::move(title), timeStart, duration,
                      employeeId);
}

void Company::deleteOrder(int id) {
    schedule.deleteOrder(id);
}

std::shared_ptr<Employee> Company::findEmployee(int id) {
    return employees.findById(id);
}

std::shared_ptr<Client> Company::findClient(int id) {
    return clients.findById(id);
}

std::shared_ptr<Order> Company::findOrder(int id) {
    return schedule.findOrder(id);
}

const std::vector<std::shared_ptr<Employee>> &Company::listEmployees() {
    return employees.listElements();
}

const std::vector<std::shared_ptr<Client>> &Company::listClients() {
    return clients.listElements();
}

const std::vector<std::shared_ptr<Order>> &Company::listVacantOrders() {
    return schedule.listVacantOrders();
}

const std::vector<std::shared_ptr<Order>> &Company::listBookedOrders() {
    return schedule.listBookedOrders();
}

int Company::getLastEmployeeId() const {
    return lastEmployeeId;
}

int Company::getLastClientId() const {
    return lastClientId;
}

int Company::getLastOrderId() const {
    return lastOrderId;
}

void Company::bookOrder(int id, int clientId) {
    schedule.bookOrder(id, clientId);
}

void Schedule::addOrder(int id,
                        std::string title,
                        int timeStart,
                        int duration,
                        int employeeId) {
    vacantOrders.add(
        Order(id, std::move(title), timeStart, duration, employeeId));
}

void Schedule::deleteOrder(int id) {
    vacantOrders.removeById(id);
    bookedOrders.removeById(id);
}

std::shared_ptr<Order> Schedule::findOrder(int id) {
    auto ptr = vacantOrders.findById(id);
    if (ptr) {
        return ptr;
    } else {
        return bookedOrders.findById(id);
    }
}

const std::vector<std::shared_ptr<Order>> &Schedule::listVacantOrders() {
    return vacantOrders.listElements();
}

const std::vector<std::shared_ptr<Order>> &Schedule::listBookedOrders() {
    return bookedOrders.listElements();
}

void Schedule::bookOrder(int id, int clientId) {
    auto order = vacantOrders.findById(id);
    if (!order) {
        std::cerr << "Incorrect order id"
                  << "\n";
        return;
    }
    order->clientId = clientId;
    bookedOrders.addByPtr(order);
    vacantOrders.removeById(id);
}

void Employee::stdPrint() const {
    std::cout << "Employee:{" << id << ", " << fullName << "} ";
}

void Client::stdPrint() const {
    std::cout << "Client:{" << id << ", " << fullName << "} ";
}

void Order::stdPrint() const {
    std::cout << "Order:{" << id << ", " << timeStart << ", " << duration
              << ", " << clientId << ", " << employeeId << "}";
}
}  // namespace dataBase