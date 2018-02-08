//
// Created by Trevor on 2/5/2018.
//

#include "SingleDigit.h"

/**
 * Constructor for SingleDigit, does not point to previous digit, usually used for the first digit only
 * @param character the character for this digit
 */
SingleDigit::SingleDigit(char character) {
    value = ((int) character) - 48;
    next = nullptr;
    previous = nullptr;
}

/**
 * Constructor for SingleDigit, points to previous digit, usually used for any digit after the first
 * @param character  the character for this digit
 * @param previousDigit pointer to the previous SingleDigit object
 */
SingleDigit::SingleDigit(char character, SingleDigit* previousDigit) {
    value = ((int) character) - 48;
    next = nullptr;
    previous = previousDigit;
}

/**
 * Set the next pointer
 * @param nextDigit the next digit that should be pointed to
 */
void SingleDigit::setNext(SingleDigit* nextDigit) {
    next = nextDigit;
}

/**
 * Gets the value of the digit as an int
 * @return int value of the digit
 */
int SingleDigit::getValue() {
    return value;
}

/**
 * Indicates whether or not there is a pointer to a next SingleDigit object
 * @return true if there is a pointer set, false if there is not
 */
bool SingleDigit::hasNext() {
    return (bool) next;
}

/**
 * Gets a pointer to the next SingleDigit object, does not remove or modify the digit
 * @return pointer to the next SingleDigit object
 */
SingleDigit* SingleDigit::getNext() {
    return next;
}

/**
 * Indicates whether or not there is a pointer to a previous SingleDigit object
 * @return true if there is a pointer set, false if there is not
 */
bool SingleDigit::hasPrevious() {
    return (bool) previous;
}

/**
 * Gets a pointer to the previous SingleDigit object, does not remove or modify the digit
 * @return pointer to the previous SingleDigit object
 */
SingleDigit* SingleDigit::getPrevious() {
    return previous;
}

