#include <iostream>
#include <string>
#include <vector>
#include "Digit.cpp"
#include "Number.cpp"
#include "DigitContainer.cpp"

using namespace std;

string readExpression();
void interpretInput(string);
DigitContainer* createNumberList(string);

const char validOperators[] = {'+', '*', '^'};
const char delimiter = (char) " ";

int main() {

    // loop so that we
    string userInput;
    while (userInput != "exit") {

        // get input from the user
        cout << "Enter calculation in RPN form, or type \"exit\" to close the application" << endl;
        string userInput = readExpression();
        cout << "user input: " << userInput  << endl;

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

void interpretInput(string userInput) {

    vector<char> characters(userInput.c_str(), userInput.c_str() + userInput.size() + 1);

    Number* numberStack = nullptr;

    string currentChunk;
    for (int i = 0; i < characters.size(); ++i) {

        if (characters[i] == (char) "+") {

        } else if  (characters[i] == (char) "*") {

        } else if (characters[i] == (char) "^") {

        } else if (characters[i] == delimiter && !currentChunk.empty()) {
            // create a number

            if (numberStack) {
                numberStack = &(new Number(currentChunk, numberStack));
            } else {
                numberStack = &new Number(currentChunk);
            }


        } else {
            currentChunk += characters[i];
        }


        cout << characters[i] << endl;
    }

}

DigitContainer* createNumberList(string numberInput, DigitContainer* previousDigitContainer) {



}





