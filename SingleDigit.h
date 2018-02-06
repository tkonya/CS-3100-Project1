//
// Created by Trevor on 2/5/2018.
//

#ifndef PROJECT1_SINGLEDIGIT_H
#define PROJECT1_SINGLEDIGIT_H

class SingleDigit {
    public:
        SingleDigit(char character);
        SingleDigit(char character, SingleDigit* previousDigit);
        void setNext(SingleDigit *nextDigit);
        int getValue();
        bool hasNext();
        SingleDigit* getNext();
        bool hasPrevious();
        SingleDigit* getPrevious();

    private:
        int value;
        SingleDigit* next;
        SingleDigit* previous;

};


#endif //PROJECT1_SINGLEDIGIT_H
