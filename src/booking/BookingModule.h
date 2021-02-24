//
// Created by Ксюша on 16.02.2021.
//

#ifndef BTIMETABLE_BOOKINGMODULE_H
#define BTIMETABLE_BOOKINGMODULE_H

#include <iostream>
#include "../dataBase/TestDataBase.h"

class BookingModule {
public:
    long long id = -1;
    std::string email, telephone;

    BookingModule() = default;
    void enterId();

    void enterTelephone();

    void enterEmail();

    static bool isValidId(long long &);

    static bool isValidTelephone(std::string &);

    static bool isValidEmail(std::string &);

    void run(dataBase::TestDataBase);
};


#endif //BTIMETABLE_BOOKINGMODULE_H
