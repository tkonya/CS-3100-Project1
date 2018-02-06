//
// Created by Trevor on 2/5/2018.
//

#include "WholeNumber.h"
#include <utility>
#include <iostream>

using namespace std;

WholeNumber::WholeNumber(string input) {
    bottomNumber = nullptr;
    buildDigits(std::move(input));
    printNumber();
}

WholeNumber::WholeNumber(string input, WholeNumber* bottomWholeNumber) {
    bottomNumber = bottomWholeNumber;
    buildDigits(std::move(input));
    printNumber();
}

void WholeNumber::buildDigits(string input) {

    vector<char> characters(input.c_str(), input.c_str() + input.size() + 1);

    rightMostDigit = nullptr;
    leftMostDigit = nullptr;

    // build the linked list, from left to right
    for (char character : characters) {
        if (character > 47 && character < 58) { // ascii 48-57 are numbers, do not accept anything else
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
        }
    }
}

void WholeNumber::setBottomNumber(WholeNumber* bottomWholeNumber) {
    bottomNumber = bottomWholeNumber;
}

void WholeNumber::printNumber() {
    if (leftMostDigit) {
        printDigit(leftMostDigit);
    }
}

void WholeNumber::printDigit(SingleDigit* digit) {
    cout << digit->getValue();
    if (digit->hasNext()) {
        printDigit(digit->getNext());
    } else {
        cout << endl;
    }
}
