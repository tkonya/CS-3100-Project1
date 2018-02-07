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
        ~WholeNumber();
        WholeNumber* bottomNumber;
        void setBottomNumber(WholeNumber* bottomNumber);
        int getSize();
        int getValueAtIndex(int index);
        string getNumber();
        void printNumber();
        bool isEmpty();
        SingleDigit* getLeftMostDigit();
        SingleDigit* getRightMostDigit();
        void x10();
        int getIntValue();
    private:
        string getDigit();
        SingleDigit* leftMostDigit;
        SingleDigit* rightMostDigit;
        void buildDigits(string input);
        void deleteDigit(SingleDigit* targetDigit);
        void printDigit(SingleDigit * digit);
        int size;
        string getDigit(SingleDigit *digit);

};


#endif //PROJECT1_WHOLENUMBER_H
