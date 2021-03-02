//
// Created by Ксюша on 24.02.2021.
//

#ifndef BTIMETABLE_TESTDATABASE_H
#define BTIMETABLE_TESTDATABASE_H

#include <vector>
#include "Entities.h"

namespace dataBase {
class TestDataBase {
public:
    std::vector<Company> companies;

    void make();
};
}  // namespace dataBase

#endif  // BTIMETABLE_TESTDATABASE_H
