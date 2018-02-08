//
// Created by Trevor on 2018-02-05.
//

#include "NumberStack.h"

/**
 * Adds a WholeNumber object (pointer) to the top of the stack
 * @param wholeNumber the WholeNumber object pointer that is to be added to the top of the stack
 */
void NumberStack::push(WholeNumber *wholeNumber) {

    // if there is anything there, we need to make sure the top number knows about it
    if (topNumber) {
        wholeNumber->setBottomNumber(topNumber);
    }

    ++size;
    topNumber = wholeNumber;
//    cout << "Pushed number (" << wholeNumber->getNumber() << ") - Stack size now " << size << endl;
}

/**
 * Removes a WholeNumber object (pointer) to the top of the stack and returns it to the caller
 * @param wholeNumber the WholeNumber object pointer that is removed and returned
 */
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

/**
 * Indicates whether the stack is empty or not
 * @return true if the stack is empty, false if the stack is not empty
 */
bool NumberStack::isEmpty() {
    return size == 0;
}

/**
 * Gets the size of the stack, in the form of an int
 * @return the size of the stack, or the number of nodes
 */
int NumberStack::getSize() {
    return size;
}

/**
 * Constructor for the stack, takes nothing, merely initializes the stack
 */
NumberStack::NumberStack() {
    size = 0;
    topNumber = nullptr;
}

/**
 * Destructor for the stack
 */
NumberStack::~NumberStack() {
    if (topNumber) {
        deleteNumber(topNumber);
    }
}

/**
 * Recursively delete all WholeNumber objects from the stack
 * @param wholeNumber
 */
void NumberStack::deleteNumber(WholeNumber *wholeNumber) {
    if (wholeNumber->bottomNumber) {
        deleteNumber(wholeNumber->bottomNumber);
    }
    delete wholeNumber;
}

