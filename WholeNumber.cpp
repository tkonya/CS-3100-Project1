//
// Created by Trevor on 2/5/2018.
//

#include "WholeNumber.h"
#include <utility>
#include <iostream>

using namespace std;

/**
 * Constructor for the WholeNumber that just takes a string input
 * @param input string, ostensibly containing at least some digits
 */
WholeNumber::WholeNumber(string input) {
    bottomNumber = nullptr;
    buildDigits(std::move(input));
}

/**
 * Constructor for the WholeNumber that takes both string input and a pointer to another WholeNumber
 * @param input input string, ostensibly containing at least some digits
 * @param bottomWholeNumber a number is to be pointed to, indicating that this one is on top of that one
 */
WholeNumber::WholeNumber(string input, WholeNumber* bottomWholeNumber) {
    bottomNumber = bottomWholeNumber;
    buildDigits(std::move(input));
}

/**
 * Takes a string, parses the digits from it, and builds the digit nodes
 * Doesn't matter if in anything other than digits is passed in, it will ignore any non-digit characters
 * @param input string, ostensibly containing at least some digits
 */
void WholeNumber::buildDigits(string input) {

    vector<char> characters(input.c_str(), input.c_str() + input.size() + 1);

    rightMostDigit = nullptr;
    leftMostDigit = nullptr;
    size = 0;

    // build the linked list, from left to right
    for (char character : characters) {
        if (character > 47 && character < 58 && !(!rightMostDigit && character == 48)) { // only accept ascii 48-57, do not accept any leading zeros
            if (rightMostDigit) {
                // save location of current rightmost digit
                SingleDigit* currentRmd = rightMostDigit;
                // make the new rightmost digit, passing in the address of the current rightmost digit so it knows what to point to with previous
                rightMostDigit = new SingleDigit(character, currentRmd);
                // go back and add the next address to the previously rightmost digit
                currentRmd->setNext(rightMostDigit);
            } else {
                rightMostDigit = new SingleDigit(character);
                // the first digit is the permanent leftmost digit, and temporarily the rightmost digit, only set this once
                leftMostDigit = rightMostDigit;
            }
            ++size;
        }
    }

    // if we stored nothing it may be because either 1) nothing was passed in, or 2) only zeroes were passed in
    // either way, default to zero
    if (!rightMostDigit && !leftMostDigit && input.find('0') != string::npos) {
        rightMostDigit = new SingleDigit('0');
        leftMostDigit = rightMostDigit;
    }
}

/**
 * Multiply the current number by 10. This is accomplished simply by adding a zero to the right side
 */
void WholeNumber::x10() {
    SingleDigit* currentRmd = rightMostDigit;
    rightMostDigit = new SingleDigit('0', currentRmd);
    currentRmd->setNext(rightMostDigit);
    ++size;
}

/**
 * Set the bottom number
 * @param bottomWholeNumber the WholeNumber that is designated as being below the current WholeNumber
 */
void WholeNumber::setBottomNumber(WholeNumber* bottomWholeNumber) {
    bottomNumber = bottomWholeNumber;
}

/**
 * Gets the WholeNumber in the form of a string
 * @return
 */
string WholeNumber::getNumber() {
    if (leftMostDigit) {
        return getDigit(leftMostDigit);
    } else {
        return "0";
    }
}

/**
 * Recursively returns the string value of the passed in digit, and all digits to the right of it
 * @param digit
 * @return
 */
string WholeNumber::getDigit(SingleDigit* digit) {
    if (digit->hasNext()) {
        return to_string(digit->getValue()).append(getDigit(digit->getNext()));
    } else {
        return to_string(digit->getValue());
    }
}

/**
 * Recursively prints the digit and all digits to the right
 * @param digit
 */
void WholeNumber::printDigit(SingleDigit* digit) {
    cout << digit->getValue();
    if (digit->hasNext()) {
        printDigit(digit->getNext());
    } else {
        cout << endl;
    }
}

/**
 * Get the size of the whole number, or the number of digits it contains
 * @return the number of digit nodes
 */
int WholeNumber::getSize() {
    return size;
}


/**
 * Returns an int for the value of the digit at a given index
 * Indexed from the right, so 0 would return the right-most digit, any index beyond the size of the list returns zero
 * @param index the index for which the value is needed
 * @return the value of the digit at the specified index, or zero if there is no digit at that position
 */
int WholeNumber::getValueAtIndex(int index) {
    if (index > size - 1) {
        return 0;
    }
    SingleDigit* currentDigit = rightMostDigit;
    while (true) {
        if (index < 0) {
            cout << "ERROR: how this happened, I have no idea" << endl;
        } else if (index == 0) {
            return currentDigit->getValue();
        }
        currentDigit = currentDigit->getPrevious();
        index--;
    }
}

/**
 * The destructor, deletes all digits
 */
WholeNumber::~WholeNumber() {
    // delete digits from left to right
    if (leftMostDigit) {
        deleteDigit(leftMostDigit);
    }
}

/**
 * Recursively deletes a digit and all digits to the right of it, used by the destructor
 * @param targetDigit
 */
void WholeNumber::deleteDigit(SingleDigit* targetDigit) {
    if (targetDigit->hasNext()) {
        deleteDigit(targetDigit->getNext());
    }
    delete targetDigit;
}

/**
 * Check if the WholeNumber object is empty, this could happen if a string containing no digits was passed in to the constructor
 * @return true if the WholeNumber is empty, false if it contains number(s)
 */
bool WholeNumber::isEmpty() {
    return !leftMostDigit && !rightMostDigit;
}

/**
 * Get the leftmost SingleDigit object
 * @return a SingleDigit object pointer
 */
SingleDigit *WholeNumber::getLeftMostDigit() {
    return leftMostDigit;
}

/**
 * Get the rightmost SingleDigit object, this is the digit in the ones place
 * @return a SingleDigit object pointer
 */
SingleDigit *WholeNumber::getRightMostDigit() {
    return rightMostDigit;
}

/**
 * Get an integer value for the number
 * @return
 */
int WholeNumber::getIntValue() {
    return stoi(getNumber());
}




