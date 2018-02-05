//
// Created by Trevor on 2/5/2018.
//

#include "SingleDigit.h"

SingleDigit::SingleDigit(char character) {
    value = (int) character;
    previous = nullptr;
    next = nullptr;
}

SingleDigit::SingleDigit(char character, SingleDigit* previousDigit) {
    value = (int) character;
    previous = previousDigit;
    next = nullptr;
}

void SingleDigit::setNext(SingleDigit* nextDigit) {
    next = nextDigit;
}