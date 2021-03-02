#include "TestDataBase.h"

namespace dataBase {
void TestDataBase::make() {
    Company A = Company("A");
    Employee emp1 = Employee(436472472, "Anna"),
             emp2 = Employee(36273672, "Vera"),
             emp3 = Employee(7446254, "Ivan");
    A.addEmployee(emp1.full_name);
    A.addEmployee(emp2.full_name);
    A.addEmployee(emp3.full_name);

    A.addOrder("I", 0, 3, emp1.id);
    A.addOrder("did", 6, 2, emp1.id);
    A.addOrder("this", 9, 1, emp3.id);
    A.addOrder("at", 1, 1, emp2.id);
    A.addOrder("3 a.m.", 6, 2, emp3.id);

    companies.push_back(A);
}
}  // namespace dataBase