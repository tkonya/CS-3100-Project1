//
// Created by Trevor on 2/5/2018.
//

#ifndef PROJECT1_WHOLENUMBER_H
#include <string>
#include <vector>
#include "SingleDigit.h"

#define PROJECT1_WHOLENUMBER_H

using namespace std;

class WholeNumber {
    public:
        WholeNumber(string input);

    private:
        SingleDigit* leftMostDigit;
        SingleDigit* rightMostDigit;
};


#endif //PROJECT1_WHOLENUMBER_H
