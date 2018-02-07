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
        WholeNumber(string input, WholeNumber* bottomNumber);
        WholeNumber* bottomNumber;
        void setBottomNumber(WholeNumber* bottomNumber);
        int getSize();
        int getValueAtIndex(int index);

    void printNumber();

private:
        SingleDigit* leftMostDigit;
        SingleDigit* rightMostDigit;
        void buildDigits(string input);

    void printDigit(SingleDigit * digit);
        int size;
};


#endif //PROJECT1_WHOLENUMBER_H
