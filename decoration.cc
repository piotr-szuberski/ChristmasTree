#include "decoration.h"

Price Decoration::getPrice() const {
    return price_;
}

std::string Decoration::getName() const {
    return name_;
}

void GlassBall::doOperation(std::ostream &os) {
    if (!broken_) {
        broken_ = broken_ || randomNumber() % 4 == 0;
    }
    os << name_ << ": " << ((broken_) ? "broken" : "OK") << '\n';
}

void Lights::doOperation(std::ostream& os) {
    state_ = (state_ == 1) ? -1 : state_ + 1;
    std::string st;
    switch (state_) {
        case -1:
            st = "off";
            break;
        case 0:
            st = "constant";
            break;
        case 1:
            st = "blinking";
            break;
        default:
            assert(false);
            break;
    }
    os << name_ << ": " << st << '\n';
}

Tree::Tree(std::string name, const Price& price, const Date& date)
        : Leaf(std::move(name), price), cut_time_(date) {
    the_time_ = Date(31, 23, 59) - date;
}

void Tree::doOperation(std::ostream& os) {
    coverage_ = 100 -  ((100 * (currentDate() - cut_time_)) / the_time_);
    os << name_ << ": " << coverage_ << "% of tree covered with needles" << '\n';
}

void ChristmasTree::doOperation(std::ostream& os) {
    for (const auto& decoration : decorations_) {
        decoration->doOperation(os);
    }
}

void ChristmasTree::addDecoration(std::shared_ptr<Decoration> dec_ptr) {
    decorations_.emplace_back(dec_ptr);
    price_ = price_ + dec_ptr->getPrice();
    notify();
}

void ChristmasTree::notify() {
    for (auto& observer : observers_) {
        observer->reaction(*this);
    }
}

void ChristmasTree::removeDecoration(
    std::list<std::shared_ptr<Decoration>>::iterator dec_ptr) {
    decorations_.remove(*dec_ptr);
    notify();
}


std::list<std::shared_ptr<Decoration>>::iterator ChristmasTree::begin() {
    return decorations_.begin();
}

std::list<std::shared_ptr<Decoration>>::iterator ChristmasTree::end() {
    return decorations_.end();
}

void ChristmasTree::attachObserver(std::shared_ptr<Person> person_ptr) {
    observers_.emplace_back(person_ptr);
}

void ChristmasTree::detachObserver(std::shared_ptr<Person> person_ptr) {
    observers_.remove(person_ptr);
}
