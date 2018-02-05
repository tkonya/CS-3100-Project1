//#pragma once
//#include <string>
//#include <vector>
//#include "RpnDigit.cpp"
//
////
//// Created by Trevor on 2018-02-03.
////
//
//using namespace std;
//
//class RpnNumber {
//    public:
//        RpnNumber(string input);
//
//    private:
//        RpnDigit* leftMostDigit;
//        RpnDigit* rightMostDigit;
//};
//
//RpnNumber::RpnNumber(string input) {
//    vector<char> characters(input.c_str(), input.c_str() + input.size() + 1);
//
//    for (int i = 0; i < characters.size(); ++i) {
//
//        if (rightMostDigit) {
//            rightMostDigit = new RpnDigit(characters[i], rightMostDigit);
//        } else {
//            rightMostDigit = new RpnDigit(characters[i], nullptr);
//            leftMostDigit = rightMostDigit;
//        }
//    }
//
//}