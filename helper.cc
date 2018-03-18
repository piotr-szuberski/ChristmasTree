#include "helper.h"

int randomNumber() {
    static std::mt19937 seed(0);
    static std::uniform_int_distribution<> rnd(0, std::numeric_limits<int>::max());
    return rnd(seed);
}

Date& currentDate() {
    static Date current_date(18, 16, 0);
    return current_date;
}


Price& Price::operator-=(const Price& other) {
    this->pln_ -= other.pln_;
    return *this;
}

bool Price::operator<(const Price& other) const {
    return this->pln_ < other.pln_;
}

Date::Date(int day = 0, int hour = 0, int minute = 0) :
        day_(day), hour_(hour), minute_(minute) {
    assert(day <= 31 && day >= 1);
    assert(hour >= 0 && hour <= 23);
    assert(minute >= 0 && minute <= 59);
}

Date& Date::operator++() {
    minute_++;
    if (minute_ == 60) {
        minute_ = 0;
        hour_++;
    }
    if (hour_ == 24) {
        hour_ = 0;
        day_++;
    }
    assert(day_ <= 31);
    return *this;
}


bool Date::operator<(const Date& other) const {
    if (this->day_ != other.day_)
        return this->day_ < other.day_;
    if (this->hour_ != other.hour_)
        return this->hour_ < other.hour_;
    return this->minute_ < other.minute_;
}
