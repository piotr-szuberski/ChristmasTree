#include "person.h"

const std::string& Person::getName() const {
    return name_;
}

void Adult::buyDecoration(const Decoration& decoration) {
    savings_ -= decoration.getPrice();
}

const Price& Adult::getSavings() const {
    return savings_;
}

void Adult::reaction(ChristmasTree& cht) const {
    std::cout << "We have new decoration!\nTotal cost is "
              << cht.getPrice() << ".\n";
}

void Child::reaction(ChristmasTree& cht) const {
    std::cout << "Wow!\n";
    (*(--cht.end())).get()->doOperation(std::cout);
}
