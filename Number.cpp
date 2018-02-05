#include <string>
#include <vector>
#include "Digit.cpp"

//
// Created by Trevor on 2018-02-03.
//

using namespace std;

class Number {
public:
    Number(string input);

private:
    Digit* leftMostDigit;
    Digit* rightMostDigit;
};

Number::Number(string input) {
    vector<char> characters(input.c_str(), input.c_str() + input.size() + 1);

    for (int i = 0; i < characters.size(); ++i) {

        if (rightMostDigit) {
            rightMostDigit = new Digit(characters[i], rightMostDigit);
        } else {
            rightMostDigit = new Digit(characters[i]);
            leftMostDigit = rightMostDigit;
        }
    }

}