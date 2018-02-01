#include <iostream>
#include <string>

using namespace std;

void readUserInput();

int main() {

    string userEntry = "";
    while (userEntry != "exit") {

    }

    return 0;
}


void readExpression() {
    string entry;
    string fullEntry = "";
    int blankLines = 0;

    while (blankLines < 2) {
        getline(cin, entry);
        if (entry == "") {

        }
    }

    getline(cin, entry);
    cout << "user input: " << entry << endl;
}