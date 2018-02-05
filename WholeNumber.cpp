//
// Created by Trevor on 2/5/2018.
//

#include "WholeNumber.h"
#include "SingleDigit.h"
#include <string>
#include <vector>

WholeNumber::WholeNumber(string input) {
    vector<char> characters(input.c_str(), input.c_str() + input.size() + 1);

    for (int i = 0; i < characters.size(); ++i) {

        if (rightMostDigit) {
            rightMostDigit = new SingleDigit(characters[i], rightMostDigit);
        } else {
            rightMostDigit = new SingleDigit(characters[i], nullptr);
            leftMostDigit = rightMostDigit;
        }
    }

}