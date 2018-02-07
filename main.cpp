#include <iostream>
#include <vector>
#include <cmath>
#include "WholeNumber.h"
#include "NumberStack.h"

using namespace std;

string readExpression();
void interpretInput(const string &);
WholeNumber* add(WholeNumber* operand1, WholeNumber* operand2);
void test(int testQuantity);
string addGetStringResult(WholeNumber *operand1, WholeNumber *operand2);
WholeNumber* multiply(WholeNumber* operand1, WholeNumber* operand2);
WholeNumber* exponentiate(WholeNumber* operand1, WholeNumber* operand2);

const char validOperators[] = {'+', '*', '^'};
const char delimiter = ' ';

int main() {

    // loop so that we
    string userInput;
    while (userInput != "exit") {

        // get input from the user
        cout << "Enter calculation in RPN form, or type \"exit\" to close the application" << endl;
        userInput = readExpression();
        cout << "user input: " << userInput << endl;

        if (userInput.find("test") != string::npos) {
            // run the automated test
            test(100000);
        } else {
            // decipher the input
            interpretInput(userInput);
            cout << endl << "------------------------" << endl;
        }


    }

    cout << "Thank you, goodbye";
    exit(EXIT_SUCCESS);
}

void test(int testQuantity) {

    int operand1Int;
    int operand2Int;
    int passed = 0;
    int failed = 0;
    WholeNumber* operand1WholeNumber;
    WholeNumber* operand2WholeNumber;
    WholeNumber* result;

    cout << "TESTING ADDITION" << endl;
    for (int i = 0; i < testQuantity / 3; ++i) {
        operand1Int = rand() % 1000000;
        operand2Int = rand() % 1000000;
        operand1WholeNumber = new WholeNumber(to_string(operand1Int));
        operand2WholeNumber = new WholeNumber(to_string(operand2Int));
        result = add(operand1WholeNumber, operand2WholeNumber);

        if (result->getIntValue() == (operand1Int + operand2Int)) {
            cout << "SUCCESS: Addition operation: " << operand1WholeNumber->getNumber() << " + " << operand2WholeNumber->getNumber() << " = " << result->getNumber() << endl;
            ++passed;
        } else {
            cout << "FAILURE: Addition operation: " << operand1WholeNumber->getNumber() << " + " << operand2WholeNumber->getNumber() << " = " << result->getNumber() << endl;
            ++failed;
        }
    }

    cout << "TESTING MULTIPLICATION" << endl;
    for (int i = 0; i < testQuantity / 3; ++i) {
        operand1Int = rand() % 46340;
        operand2Int = rand() % 46340;
        operand1WholeNumber = new WholeNumber(to_string(operand1Int));
        operand2WholeNumber = new WholeNumber(to_string(operand2Int));
        result = multiply(operand1WholeNumber, operand2WholeNumber);

        if (result->getIntValue() == (operand1Int * operand2Int)) {
            cout << "SUCCESS: Multiplication operation: " << operand1WholeNumber->getNumber() << " * " << operand2WholeNumber->getNumber() << " = " << result->getNumber() << endl;
            ++passed;
        } else {
            cout << "FAILURE: Multiplication operation: " << operand1WholeNumber->getNumber() << " * " << operand2WholeNumber->getNumber() << " = " << result->getNumber() << endl;
            ++failed;
        }
    }

    cout << "TESTING EXPONENTIATION" << endl;
    for (int i = 0; i < testQuantity / 3 + (testQuantity - (testQuantity / 3) * 3); ++i) {
        operand1Int = rand() % 9;
        operand2Int = rand() % 9;
        operand1WholeNumber = new WholeNumber(to_string(operand1Int));
        operand2WholeNumber = new WholeNumber(to_string(operand2Int));
        result = exponentiate(operand1WholeNumber, operand2WholeNumber);

        if (result->getIntValue() == pow(operand2Int, operand1Int)) {
            cout << "SUCCESS: Exponentiation operation: " << operand2WholeNumber->getNumber() << " ^ " << operand1WholeNumber->getNumber() << " = " << result->getNumber() << endl;
            ++passed;
        } else {
            cout << "FAILURE: Exponentiation operation: " << operand2WholeNumber->getNumber() << " ^ " << operand1WholeNumber->getNumber() << " = " << result->getNumber() << endl;
            ++failed;
        }
    }

    cout << endl << "Test complete: " << passed << " passed, " << failed << " failed" << endl << "-------------------------------------" << endl;
}

string readExpression() {
    string entry;
    string fullEntry;

    while (true) {
        getline(cin, entry);
        if (entry.empty()) {
            break;
        } else if (entry == "exit") {
            // even if they have entered calculations on previous lines, exit when exit is typed
            return "exit";
        } else {
            fullEntry += " " + entry;
        }
    }

    return fullEntry;
}

void interpretInput(const string &userInput) {

    // intialize the stack
    NumberStack* numberStack = new NumberStack();

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

    // possibly add the last number to the stack
    if (!currentChunk.empty() && currentChunk.length() > 0) {
        WholeNumber* finalNumber = new WholeNumber(currentChunk);
        if (!finalNumber->isEmpty()) {
            numberStack->push(finalNumber);
        } else {
            delete finalNumber;
        }
    }

    if (numberStack->getSize() == 1) {
        cout << endl <<"Result of all operations: ";
        numberStack->pop()->printNumber();
        cout << endl;
    } else {
        cout << "Error: incorrect number of operators or operands" << endl;
    }

    delete numberStack;
}

WholeNumber* add(WholeNumber* operand1, WholeNumber* operand2) {
    return new WholeNumber(addGetStringResult(operand1, operand2));
}

string addGetStringResult(WholeNumber *operand1, WholeNumber *operand2) {
    int maxSize;
    if (operand1->getSize() > operand2->getSize()) {
        maxSize = operand1->getSize();
    } else {
        maxSize = operand2->getSize();
    }

    string newValue;

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

//    cout << "Addition operation: " << operand1->getNumber() << " + " << operand2->getNumber() << " = " << totalResult << endl;
    return totalResult;
}

WholeNumber* multiply(WholeNumber* operand1, WholeNumber* operand2) {

    WholeNumber* total = new WholeNumber("0");
    for (int i = 0; i < operand2->getSize(); ++i) {

        // do one round of multiplication per digit in operator2
        int multiplier = operand2->getValueAtIndex(i);
        WholeNumber* subTotal = new WholeNumber("0");
        for (int k = 0; k < multiplier; ++k) {
            subTotal = new WholeNumber(addGetStringResult(operand1, subTotal));
        }

        // add as many zeroes as we need to the number
        for (int x = 0; x < i; ++x) {
            subTotal->x10();
        }

        total = new WholeNumber(addGetStringResult(total, subTotal));
    }

//    cout << "Multiplication operation: " << operand1->getNumber() << " * " << operand2->getNumber() << " = " << total->getNumber() << endl;
    return total;
}

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






