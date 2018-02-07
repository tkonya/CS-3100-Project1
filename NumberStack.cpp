//
// Created by Trevor on 2018-02-05.
//

#include <iostream>
#include "NumberStack.h"

void NumberStack::push(WholeNumber *wholeNumber) {

    // if there is anything there, we need to make sure the top number knows about it
    if (topNumber) {
        wholeNumber->setBottomNumber(topNumber);
    }

    ++size;
    topNumber = wholeNumber;
//    cout << "Pushed number (" << wholeNumber->getNumber() << ") - Stack size now " << size << endl;
}

WholeNumber *NumberStack::pop() {

    // hold onto the current top number pointer locally
    WholeNumber* currentTop = topNumber;

    // move the pointer down to whatever is below the current top, if there is anything
    if (currentTop->bottomNumber) {
        topNumber = currentTop->bottomNumber;
    } else {
        topNumber = nullptr;
    }

    --size;
//    cout << "Popped number (" << currentTop->getNumber() << ") - Stack size now " << size << endl;
    return currentTop;
}

bool NumberStack::isEmpty() {
    return size == 0;
}

int NumberStack::getSize() {
    return size;
}

NumberStack::NumberStack() {
    size = 0;
    topNumber = nullptr;
}

NumberStack::~NumberStack() {
    if (topNumber) {
        deleteNumber(topNumber);
    }
}

void NumberStack::deleteNumber(WholeNumber *wholeNumber) {
    if (wholeNumber->bottomNumber) {
        deleteNumber(wholeNumber->bottomNumber);
    }
    delete wholeNumber;
}

