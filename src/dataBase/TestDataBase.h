//
// Created by Ксюша on 24.02.2021.
//

#ifndef BTIMETABLE_TESTDATABASE_H
#define BTIMETABLE_TESTDATABASE_H

#include "Entities.h"
#include <vector>

namespace dataBase {
    class TestDataBase {
    public:
        std::vector<Company> companies;

        void make();

    };
}

#endif //BTIMETABLE_TESTDATABASE_H
