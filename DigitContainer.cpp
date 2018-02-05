//
// Created by Trevor on 2018-02-03.
//

class DigitContainer {

    public:
        DigitContainer();
        DigitContainer(int *leftMostDigit, int *rightMostDigit);

    private:
        int* leftMostDigit;
        int* rightMostDigit;
};

DigitContainer::DigitContainer(int* left, int* right) {
    leftMostDigit = left;
    rightMostDigit = right;
}
