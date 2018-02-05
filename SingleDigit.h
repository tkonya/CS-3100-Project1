//
// Created by Trevor on 2/5/2018.
//

#ifndef PROJECT1_SINGLEDIGIT_H
#define PROJECT1_SINGLEDIGIT_H

class SingleDigit {
    public:
        SingleDigit(char character);
        SingleDigit(char character, SingleDigit* previousDigit);

    private:
        int value;
        SingleDigit* next;
        SingleDigit* previous;

        void setNext(SingleDigit *nextDigit);
};


#endif //PROJECT1_SINGLEDIGIT_H
