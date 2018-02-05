//#pragma once
//
//class RpnDigit {
//    public:
//        RpnDigit(char character);
//        RpnDigit(char character, RpnDigit* previousDigit);
//
//    private:
//        int value;
//        RpnDigit* next;
//        RpnDigit* previous;
//
//    void setNext(RpnDigit *nextDigit);
//};
//
//RpnDigit::RpnDigit(char character) {
//    value = (int) character;
//    previous = nullptr;
//    next = nullptr;
//}
//
//RpnDigit::RpnDigit(char character, RpnDigit* previousDigit) {
//    value = (int) character;
//    previous = previousDigit;
//    next = nullptr;
//}
//
//void RpnDigit::setNext(RpnDigit* nextDigit) {
//    next = nextDigit;
//}
