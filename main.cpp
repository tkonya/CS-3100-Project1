#include <iostream>
#include <string>
#include <vector>
#include "WholeNumber.h"
#include "NumberStack.h"

using namespace std;

string readExpression();
void interpretInput(const string &);
WholeNumber* add(WholeNumber* operand1, WholeNumber* operand2);
WholeNumber* multiply(WholeNumber* operand1, WholeNumber* operand2);
WholeNumber* exponentiate(WholeNumber* operand1, WholeNumber* operand2);

const char validOperators[] = {'+', '*', '^'};
const char delimiter = ' ';

NumberStack* numberStack;

int main() {

    // intialize the stack
    numberStack = new NumberStack();

    // loop so that we
    string userInput;
    while (userInput != "exit") {

        // get input from the user
        cout << "Enter calculation in RPN form, or type \"exit\" to close the application" << endl;
        userInput = readExpression();
        cout << "user input: " << userInput << endl;

        // decipher the input
        interpretInput(userInput);

    }

    cout << "Thank you, goodbye";
    exit(EXIT_SUCCESS);
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
                numberStack->push(add(operand1, operand2));
            } else if (character == validOperators[2]) {
                numberStack->push(add(operand1, operand2));
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

    if (numberStack->getSize() == 1) {
        cout << "Result of all operations: ";
        numberStack->pop()->printNumber();
        cout << endl;
    } else {
        cout << "Error: incorrect ratio of operators or operands" << endl;
    }

}

WholeNumber* add(WholeNumber* operand1, WholeNumber* operand2) {
    int maxSize = operand1->getSize();
    if (operand2->getSize() > maxSize) {
        maxSize = operand2->getSize();
    }

    string newValue;

    int value1;
    int value2;
    int carryValue = 0;
    string currentResult;
    string totalResult;
    for (int i = 0; i < maxSize + 1; i++) { // must do max size + 1 because it is possible we would still have 5th number after adding two numbers of length 4

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

//    cout << "result of addition: " + totalResult;
    return new WholeNumber(totalResult);
}

WholeNumber* multiply(WholeNumber* operand1, WholeNumber* operand2) {




}

WholeNumber* exponentiate(WholeNumber* operand1, WholeNumber* operand2) {

}






