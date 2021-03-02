#include "Entities.h"

namespace dataBase {

template <typename T>
void Holder<T>::add(T value) {
    auto element = new T(std::move(value));
    std::shared_ptr<T> element_ptr(element);
    elements.push_back(element_ptr);
    id_map[element_ptr->id] = element_ptr;
}

template <typename T>
void Holder<T>::addByPtr(std::shared_ptr<T> element_ptr) {
    elements.push_back(element_ptr);
    id_map[element_ptr->id] = element_ptr;
}

template <typename T>
std::shared_ptr<T> Holder<T>::findById(int id) {
    return id_map[id];
}

template <typename T>
void Holder<T>::removeById(int id) {
    id_map[id].reset();
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

void Company::addEmployee(std::string full_name) {
    employees.add(Employee(++lastEmployeeId, std::move(full_name)));
}

void Company::addClient(std::string full_name) {
    clients.add(Client(++lastClientId, std::move(full_name)));
}

void Company::deleteEmployee(int id) {
    employees.removeById(id);
}

void Company::deleteClient(int id) {
    clients.removeById(id);
}

void Company::addOrder(std::string title,
                       int time_start,
                       int duration,
                       int employee_id) {
    schedule.addOrder(++lastOrderId, std::move(title), time_start, duration,
                      employee_id);
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

void Company::bookOrder(int id, int client_id) {
    schedule.bookOrder(id, client_id);
}

void Schedule::addOrder(int id,
                        std::string title,
                        int time_start,
                        int duration,
                        int employee_id) {
    vacant_orders.add(
        Order(id, std::move(title), time_start, duration, employee_id));
}

void Schedule::deleteOrder(int id) {
    vacant_orders.removeById(id);
    booked_orders.removeById(id);
}

std::shared_ptr<Order> Schedule::findOrder(int id) {
    auto ptr = vacant_orders.findById(id);
    if (ptr) {
        return ptr;
    } else {
        return booked_orders.findById(id);
    }
}

const std::vector<std::shared_ptr<Order>> &Schedule::listVacantOrders() {
    return vacant_orders.listElements();
}

const std::vector<std::shared_ptr<Order>> &Schedule::listBookedOrders() {
    return booked_orders.listElements();
}

void Schedule::bookOrder(int id, int client_id) {
    auto order = vacant_orders.findById(id);
    if (!order) {
        std::cerr << "Incorrect order id"
                  << "\n";
        return;
    }
    order->client_id = client_id;
    booked_orders.addByPtr(order);
    vacant_orders.removeById(id);
}

void Employee::stdPrint() const {
    std::cout << "Employee:{" << id << ", " << full_name << "} ";
}

void Client::stdPrint() const {
    std::cout << "Client:{" << id << ", " << full_name << "} ";
}

void Order::stdPrint() const {
    std::cout << "Order:{" << id << ", " << time_start << ", " << duration
              << ", " << client_id << ", " << employee_id << "}";
}
}  // namespace dataBase