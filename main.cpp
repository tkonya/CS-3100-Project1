#include <iostream>
#include <vector>
#include "RpnNumber.cpp"
#include "WholeNumber.h"

using namespace std;

string readExpression();
void interpretInput(const string &);

const char validOperators[] = {'+', '*', '^'};
const char delimiter = ' ';

int main() {

    // loop so that we
    string userInput;
    while (userInput != "exit") {

        // get input from the user
        cout << "Enter calculation in RPN form, or type \"exit\" to close the application" << endl;
        userInput = readExpression();
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

void interpretInput(const string &userInput) {
    cout << "interpreting input: " << userInput << endl;

    vector<char> characters(userInput.c_str(), userInput.c_str() + userInput.size() + 1);

    string currentChunk;
    for (char character : characters) {

        cout << "doing operation +" << endl;
        if (character == validOperators[0]) {

            currentChunk = "";
        } else if  (character == validOperators[1]) {
            cout << "doing operation *" << endl;

            currentChunk = "";
        } else if (character == validOperators[2]) {
            cout << "doing operation ^" << endl;

            currentChunk = "";
        } else if (character == delimiter && !currentChunk.empty()) {
            cout << "creating number: " << currentChunk << endl;

            currentChunk = "";
        } else {
            cout << "adding character " << character << " to chunk " << currentChunk << endl;
            currentChunk += character;
        }


        cout << character << endl;
    }

}






