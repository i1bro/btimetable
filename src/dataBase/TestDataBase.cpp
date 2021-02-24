//
// Created by Ксюша on 24.02.2021.
//

#include "TestDataBase.h"
namespace dataBase {
    void TestDataBase::make() {
        Company A = Company("A"), B = Company("B"), C = Company("C");
        Employee emp1 = Employee(436472472, "Anna"), emp2 = Employee(36273672, "Vera");
        A.addEmployee(emp1.id, emp1.full_name);
        B.addEmployee(emp1.id, emp1.full_name);
        C.addEmployee(emp1.id, emp1.full_name);

        A.addEmployee(emp2.id, emp2.full_name);

        A.addOrder(12345, 0, 5, 0, emp1.id);
        B.addOrder(222, 6, 2, 0, emp1.id);
        C.addOrder(1000, 9, 1, 0, emp1.id);

        A.addOrder(2345, 1, 1, 0, emp2.id);
        A.addOrder(6666, 6, 3, 0, emp2.id);

        companies.push_back(A);
        companies.push_back(B);
        companies.push_back(C);
    }
}