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
}

WholeNumber::WholeNumber(string input, WholeNumber* bottomWholeNumber) {
    bottomNumber = bottomWholeNumber;
    buildDigits(std::move(input));
}

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

void WholeNumber::x10() {
    SingleDigit* currentRmd = rightMostDigit;
    rightMostDigit = new SingleDigit('0', currentRmd);
    currentRmd->setNext(rightMostDigit);
    ++size;
}

void WholeNumber::setBottomNumber(WholeNumber* bottomWholeNumber) {
    bottomNumber = bottomWholeNumber;
}

string WholeNumber::getNumber() {
    if (leftMostDigit) {
        return getDigit(leftMostDigit);
    } else {
        return "0";
    }
}

string WholeNumber::getDigit(SingleDigit* digit) {
    if (digit->hasNext()) {
        return to_string(digit->getValue()).append(getDigit(digit->getNext()));
    } else {
        return to_string(digit->getValue());
    }
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

int WholeNumber::getSize() {
    return size;
}


// indexed from the right, so 0 would return the right-most digit
// index beyond the size of the list should return zero
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

WholeNumber::~WholeNumber() {
    // delete digits from left to right
    if (leftMostDigit) {
        deleteDigit(leftMostDigit);
    }
}

void WholeNumber::deleteDigit(SingleDigit* targetDigit) {
    if (targetDigit->hasNext()) {
        deleteDigit(targetDigit->getNext());
    }
    delete targetDigit;
}

bool WholeNumber::isEmpty() {
    return !leftMostDigit && !rightMostDigit;
}

SingleDigit *WholeNumber::getLeftMostDigit() {
    return leftMostDigit;
}

SingleDigit *WholeNumber::getRightMostDigit() {
    return rightMostDigit;
}

int WholeNumber::getIntValue() {
    return stoi(getNumber());
}



