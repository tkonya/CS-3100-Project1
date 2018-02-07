//
// Created by Trevor on 2018-02-05.
//

#ifndef PROJECT1_NUMBERSTACK_H
#define PROJECT1_NUMBERSTACK_H


#include "WholeNumber.h"

class NumberStack {
private:
    WholeNumber* topNumber;
    int size;
    void deleteNumber(WholeNumber* wholeNumber);

public:
    void push(WholeNumber* wholeNumber);
    WholeNumber* pop();
    bool isEmpty();
    int getSize();
    NumberStack();
    ~NumberStack();
};


#endif //PROJECT1_NUMBERSTACK_H
