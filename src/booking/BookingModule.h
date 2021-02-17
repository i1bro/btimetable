//
// Created by Ксюша on 16.02.2021.
//

#ifndef BTIMETABLE_BOOKINGMODULE_H
#define BTIMETABLE_BOOKINGMODULE_H

#include <iostream>

class BookingModule {
public:
    long long id;
    std::string email, telephone;

    void enterId();

    void enterTelephone();

    void enterEmail();

    static bool isValidId(long long &);

    static bool isValidTelephone(std::string &);

    static bool isValidEmail(std::string &);

    void run();
};


#endif //BTIMETABLE_BOOKINGMODULE_H
