#include "Entities.h"

namespace dataBase {

    template<typename T>
    void Holder<T>::add(T value) {
        auto element = new T(std::move(value));
        std::shared_ptr<T> element_ptr(element);
        elements.push_back(element_ptr);
        id_map[element_ptr->id] = element_ptr;
    }

    template<typename T>
    std::shared_ptr<T> Holder<T>::findById(int id) {
        return id_map[id];
    }

    template<typename T>
    void Holder<T>::removeById(int id) {
        id_map[id].reset();
        for(int ind = 0; ind < static_cast<int>(elements.size()); ind++) {
            if((elements[ind] -> id) == id) {
                elements.erase(elements.begin() + ind);
                return;
            }
        }
    }

    template<typename T>
    const std::vector<std::shared_ptr<T>> &Holder<T>::listElements() {
        return elements;
    }

    void Company::addEmployee(int id_, std::string full_name_) {
        employees.add(Employee(id_, std::move(full_name_)));
    }

    void Company::addClient(int id_, std::string full_name_) {
        clients.add(Client(id_, std::move(full_name_)));
    }

    void Company::deleteEmployee(int id) {
        employees.removeById(id);
    }

    void Company::deleteClient(int id) {
        clients.removeById(id);
    }

    void Company::addOrder(int id_, int time_start_, int duration_, int client_id, int employee_id) {
        schedule.addOrder(id_, time_start_, duration_, std::shared_ptr<Client>(clients.findById(client_id)), std::shared_ptr<Employee>(
                employees.findById(employee_id)));
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

    const std::vector<std::shared_ptr<Order>> &Company::listOrders() {
        return schedule.listOrders();
    }

    void Schedule::addOrder(int id_, int time_start_, int duration, std::shared_ptr<Client> client_, std::shared_ptr<Employee> employee_) {
        orders.add(Order(id_, time_start_, duration, std::move(client_), std::move(employee_)));
    }

    void Schedule::deleteOrder(int id) {
        orders.removeById(id);
    }

    std::shared_ptr<Order> Schedule::findOrder(int id) {
        return orders.findById(id);
    }

    const std::vector<std::shared_ptr<Order>> &Schedule::listOrders() {
        return orders.listElements();
    }

    void Employee::stdPrint() const {
        std::cout << "Employee:{" << id << ", " << full_name << "} ";
    }

    void Client::stdPrint() const {
        std::cout << "Client:{" << id << ", " << full_name << "} ";
    }

    void Order::stdPrint() const {
        std::cout << "Order:{" << id << ", " << time_start << ", " << duration << ", ";
        client->stdPrint();
        employee->stdPrint();
        std::cout << "}" << std::endl;
    }
}