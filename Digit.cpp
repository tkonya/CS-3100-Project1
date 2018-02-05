//
// Created by Trevor on 1/31/2018.
//

class Digit {
    public:
        Digit(char character);
        Digit(char character, Digit* previousDigit);
        void setNext(Digit* nextDigit);

    private:
        int value;
        Digit* next;
        Digit* previous;
};

Digit::Digit(char character) {
    value = (int) character;
    previous = nullptr;
    next = nullptr;
}

Digit::Digit(char character, Digit* previousDigit) {
    value = (int) character;
    previous = previousDigit;
    next = nullptr;
}

void Digit::setNext(Digit* nextDigit) {
    next = nextDigit;
}
