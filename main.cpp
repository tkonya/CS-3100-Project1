#include <iostream>
#include <vector>
#include <cmath>
#include <synchapi.h>
#include "WholeNumber.h"
#include "NumberStack.h"

using namespace std;

string readUserInput();
string formatInput(const string &userInput);
void interpretInput(const string &);
WholeNumber* add(WholeNumber* operand1, WholeNumber* operand2);
string addGetStringResult(WholeNumber *operand1, WholeNumber *operand2);
WholeNumber* multiply(WholeNumber* operand1, WholeNumber* operand2);
WholeNumber* exponentiate(WholeNumber* exponent, WholeNumber* base);
void test(int testQuantity);

const char validOperators[] = {'+', '*', '^'};
const char delimiter = ' ';

int main() {

    // loop so that we
    string userInput;
    while (userInput != "exit") {

        // get input from the user
        cout << "Enter calculation in RPN form, or type \"exit\" to close the application, or type \"test\" to run the automated test" << endl;
        userInput = readUserInput();

        if (userInput.find("test") != string::npos) {
            // run the automated test
            cout << "Running the automated test..." << endl;
            test(1000000);
        } else if (userInput.find("exit") == string::npos) {
            // decipher the input
            cout << "Formatted User input: " << formatInput(userInput) << endl;
            interpretInput(userInput);
            cout << endl << "------------------------" << endl;
        }

    }

    cout << "Thank you, goodbye";
    exit(EXIT_SUCCESS);
}

/**
 * Randomly generates calculations with two operands and one operator. Does a roughly equal number of tests for each of the three operators.
 * @param testQuantity
 */
void test(int testQuantity) {

    int operand1Int;
    int operand2Int;
    int passed = 0;
    int failed = 0;
    WholeNumber* operand1WholeNumber;
    WholeNumber* operand2WholeNumber;
    WholeNumber* result;

    cout << "Testing addition..." << endl;
    for (int i = 0; i < testQuantity / 3; ++i) {
        operand1Int = rand() % 1000000;
        operand2Int = rand() % 1000000;
        operand1WholeNumber = new WholeNumber(to_string(operand1Int));
        operand2WholeNumber = new WholeNumber(to_string(operand2Int));
        result = add(operand1WholeNumber, operand2WholeNumber);

        if (result->getIntValue() == (operand1Int + operand2Int)) {
//            cout << "SUCCESS: Addition operation: " << operand1WholeNumber->getNumber() << " + " << operand2WholeNumber->getNumber() << " = " << result->getNumber() << endl;
            ++passed;
        } else {
            cout << "FAILURE: Addition operation: " << operand1WholeNumber->getNumber() << " + " << operand2WholeNumber->getNumber() << " != " << result->getNumber() << endl;
            ++failed;
        }

        delete operand1WholeNumber;
        delete operand2WholeNumber;
        delete result;
    }

    cout << "Testing multiplication..." << endl;
    for (int i = 0; i < testQuantity / 3; ++i) {
        operand1Int = rand() % 46340;
        operand2Int = rand() % 46340;
        operand1WholeNumber = new WholeNumber(to_string(operand1Int));
        operand2WholeNumber = new WholeNumber(to_string(operand2Int));
        result = multiply(operand1WholeNumber, operand2WholeNumber);

        if (result->getIntValue() == (operand1Int * operand2Int)) {
//            cout << "SUCCESS: Multiplication operation: " << operand1WholeNumber->getNumber() << " * " << operand2WholeNumber->getNumber() << " = " << result->getNumber() << endl;
            ++passed;
        } else {
            cout << "FAILURE: Multiplication operation: " << operand1WholeNumber->getNumber() << " * " << operand2WholeNumber->getNumber() << " != " << result->getNumber() << endl;
            ++failed;
        }

        delete operand1WholeNumber;
        delete operand2WholeNumber;
        delete result;
    }

    cout << "Testing exponentiation..." << endl;
    for (int i = 0; i < testQuantity / 3 + (testQuantity - (testQuantity / 3) * 3); ++i) {
        operand1Int = rand() % 9;
        operand2Int = rand() % 9;
        operand1WholeNumber = new WholeNumber(to_string(operand1Int));
        operand2WholeNumber = new WholeNumber(to_string(operand2Int));
        result = exponentiate(operand1WholeNumber, operand2WholeNumber);

        if (result->getIntValue() == pow(operand2Int, operand1Int)) {
//            cout << "SUCCESS: Exponentiation operation: " << operand2WholeNumber->getNumber() << " ^ " << operand1WholeNumber->getNumber() << " = " << result->getNumber() << endl;
            ++passed;
        } else {
            cout << "FAILURE: Exponentiation operation: " << operand2WholeNumber->getNumber() << " ^ " << operand1WholeNumber->getNumber() << " != " << result->getNumber() << endl;
            ++failed;
        }

        delete operand1WholeNumber;
        delete operand2WholeNumber;
        delete result;
    }

    cout << endl << "Test complete: " << passed << " passed, " << failed << " failed" << endl << "-------------------------------------" << endl;
}

/**
 * Read input from the user, returns the input once an empty line is detected, or when "exit" or "test" is typed
 * @return
 */
string readUserInput() {
    string entry;
    string fullEntry;

    while (true) {
        getline(cin, entry);
        if (entry.empty()) {
            break;
        } else if (entry == "exit") {
            // even if they have entered calculations on previous lines, exit when exit is typed
            return "exit";
        } else if (entry == "test") {
            return "test";
        } else {
            fullEntry += " " + entry;
        }
    }

    return fullEntry;
}

string formatInput(const string &userInput) {
    string formattedInput;
    vector<char> characters(userInput.c_str(), userInput.c_str() + userInput.size() + 1);

    bool previousValueSpace = true; // initializing this to true will ensure no leading spaces are written
    for (char character : characters) {
        if ((character > 47 && character < 58) || character == 42 || character == 43 || character == 94) {
            if (character > 47 && character < 58) {
                formattedInput.append(to_string(character - 48));
            } else if (character == 43) {
                formattedInput.append("+");
            } else if (character == 42) {
                formattedInput.append("*");
            } else if (character == 94) {
                formattedInput.append("^");
            }
            previousValueSpace = false;
        } else if (character == 32 && !previousValueSpace) {
            formattedInput.append(" ");
            previousValueSpace = true;
        }
    }

    return formattedInput;
}

/**
 * Parses user input and does calculations live
 * @param userInput
 */
void interpretInput(const string &userInput) {

    // intialize the stack
    auto* numberStack = new NumberStack();

    vector<char> characters(userInput.c_str(), userInput.c_str() + userInput.size() + 1);

    string currentChunk;
    for (char character : characters) {

        if (character == validOperators[0] || character == validOperators[1] || character == validOperators[2]) {

            if (numberStack->getSize() < 2) {
                cout << "ERROR: not enough operands" << endl;
                return;
            }

            WholeNumber* operand1 = numberStack->pop();
            WholeNumber* operand2 = numberStack->pop();

            if (character == validOperators[0]) {
                numberStack->push(add(operand1, operand2));
            } else if (character == validOperators[1]) {
                numberStack->push(multiply(operand1, operand2));
            } else if (character == validOperators[2]) {
                numberStack->push(exponentiate(operand1, operand2));
            }

            // done with these now, so delete them
            delete operand1;
            delete operand2;

            currentChunk = "";
        } else if (character == delimiter && !currentChunk.empty()) {
            numberStack->push(new WholeNumber(currentChunk));
            currentChunk = "";
        } else {
            currentChunk += character;
        }
    }

    // possibly add the last number to the stack, the only legitimate use of this is if the user just enters one number, in which case the result is the same number
    // usually if we have a number at the end of a series of operators and operands, it is wrong
    if (!currentChunk.empty() && currentChunk.length() > 0) {
        WholeNumber* finalNumber = new WholeNumber(currentChunk);
        if (!finalNumber->isEmpty()) {
            numberStack->push(finalNumber);
        } else {
            delete finalNumber;
        }
    }

    // if we only have one thing left in the stack then the number of operators and operands were correct
    if (numberStack->getSize() == 1) {
        cout << "Result of all operations: ";
        WholeNumber* result = numberStack->pop();
        cout << result->getNumber() << endl;
        delete result;
    } else {
        cout << "Error: incorrect number of operators or operands" << endl;
    }

    delete numberStack;
}

/**
 * Adds two WholeNumber objects together
 * @param operand1 the first number that will be added
 * @param operand2 the second number that will be added
 * @return the result in the form of a new WholeNumber object
 */
WholeNumber* add(WholeNumber* operand1, WholeNumber* operand2) {
    return new WholeNumber(addGetStringResult(operand1, operand2));
}

/**
 * Adds two WholeNumber objects together
 * @param operand1
 * @param operand2
 * @return the result in the form of a string
 */
string addGetStringResult(WholeNumber *operand1, WholeNumber *operand2) {
    int maxSize;
    if (operand1->getSize() > operand2->getSize()) {
        maxSize = operand1->getSize();
    } else {
        maxSize = operand2->getSize();
    }

    int value1;
    int value2;
    int carryValue = 0;
    string currentResult;
    string totalResult;

    for (int i = 0; i < maxSize + 1; i++) {

        value1 = operand1->getValueAtIndex(i);
        value2 = operand2->getValueAtIndex(i);

        currentResult = to_string(value1 + value2 + carryValue);
        if (currentResult.size() > 1) {
            totalResult.insert(0, to_string(currentResult[1] - 48));
            carryValue = currentResult[0] - 48;
        } else {
            totalResult.insert(0, to_string(currentResult[0] - 48));
            carryValue = 0;
        }
    }

    cout << "Addition operation: " << operand1->getNumber() << " + " << operand2->getNumber() << " = " << totalResult << endl;
    return totalResult;
}

/**
 * Multiplies two WholeNumber objects together
 * @param operand1 the first number to be multiplied
 * @param operand2 the second number to be multipliec
 * @return the result in the form of a WholeNumber object
 */
WholeNumber* multiply(WholeNumber* operand1, WholeNumber* operand2) {

    WholeNumber* total = new WholeNumber("0");
    WholeNumber* previousTotal;
    WholeNumber* subTotal;
    WholeNumber* previousSubTotal;
    for (int i = 0; i < operand2->getSize(); ++i) {

        // do one round of multiplication per digit in operator2
        int multiplier = operand2->getValueAtIndex(i);
        subTotal = new WholeNumber("0");
        for (int k = 0; k < multiplier; ++k) {
            previousSubTotal = subTotal;
            subTotal = new WholeNumber(addGetStringResult(operand1, subTotal));
            delete previousSubTotal;
        }

        // add as many zeroes as we need to the number
        for (int x = 0; x < i; ++x) {
            subTotal->x10();
        }

        previousTotal = total;
        total = new WholeNumber(addGetStringResult(total, subTotal));
        delete previousTotal;

        delete subTotal;
    }

//    cout << "Multiplication operation: " << operand1->getNumber() << " * " << operand2->getNumber() << " = " << total->getNumber() << endl;
    return total;
}

/**
 * Exponentiate a number
 * @param exponent the exponent
 * @param base the base number to be raised to the exponent's power
 * @return the result in the form of a WholeNumber object
 */
WholeNumber* exponentiate(WholeNumber* exponent, WholeNumber* base) {
    int exponentValue = exponent->getIntValue();

    WholeNumber* total;
    if (exponentValue == 0) {
        total = new WholeNumber("1");
    } else if (exponentValue == 1) {
        total = new WholeNumber(base->getNumber());
    } else {
        total = new WholeNumber(base->getNumber());
        for (int i = 1; i < exponentValue; ++i) {
            total = multiply(total, base);
        }
        return total;
    }

//    cout << "Exponentiation operation: " << base->getNumber() << " ^ " << exponent->getNumber() << " = " << total->getNumber() << endl;
    return total;
}






