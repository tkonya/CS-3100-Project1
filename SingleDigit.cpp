//
// Created by Trevor on 2/5/2018.
//

#include "SingleDigit.h"

SingleDigit::SingleDigit(char character) {
    value = ((int) character) - 48;
    next = nullptr;
    previous = nullptr;
}

SingleDigit::SingleDigit(char character, SingleDigit* previousDigit) {
    value = ((int) character) - 48;
    next = nullptr;
    previous = previousDigit;
}

void SingleDigit::setNext(SingleDigit* nextDigit) {
    next = nextDigit;
}

int SingleDigit::getValue() {
    return value;
}

bool SingleDigit::hasNext() {
    return (bool) next;
}

SingleDigit* SingleDigit::getNext() {
    return next;
}

bool SingleDigit::hasPrevious() {
    return (bool) previous;
}

SingleDigit* SingleDigit::getPrevious() {
    return previous;
}

