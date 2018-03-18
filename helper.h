#ifndef CHRISTMASTREE_HELPER_H
#define CHRISTMASTREE_HELPER_H

#include <iostream>
#include <random>
#include <cassert>

/**
 * Deklaracje klas potrzebne do stworzenia obiektow z person.h i decoration.h
 */
class Decoration;
class ChristmasTree;
class Person;

/**
 * Funkcja zwracajaca losowe liczby, jednakowe dla kazdego wywolania programu
 * @return losowy, ale powtarzalna liczba z zakresu range_from do range_to
 */
int randomNumber();

/**
 * Klasa-opakowanie typu integer z funkcjami do obliczen pienieznych
 */
class Price {
    int pln_;

public:
    /**
     * Konstruktor inicjowany wartoscia typu int
     * @param pln - pieniadze poczatkowe
     */
    explicit Price(int pln = 0) : pln_(pln) {}

    /**
     * Operator dodawania
     * @param lhv - podawany przez wartosc, by optymalizowac operacje typu
     * a + b + c
     * @param rhv - podawany jako stala referencja
     * @return lhv += rhv
     */
    friend Price operator+(Price lhv, const Price& rhv) {
        lhv.pln_ += rhv.pln_;
        return lhv;
    }

    /**
     * Operator -=
     * @param other - wartosc o ktora zmniejsza sie cena
     * @return referencja na zmieniony obiekt
     */
    Price& operator-=(const Price&);

    /**
     * Operator porownania, porownuje pole pln_
     * @param other
     * @return this->pln_ < other->pln_
     */
    bool operator<(const Price&) const;

    /**
     * Wypisuje "pln_ PLN"
     * @param stream - wyjscie (domyslnie standardowe)
     * @param price
     * @return referencja na podane wyjscie
     */
    friend std::ostream& operator<<(std::ostream& stream, const Price& price) {
        return stream << price.pln_ << " PLN";
    }
};

/**
 * Klasa odpowiadajaca za obsługe dat wraz z godzina (czas) ograniczonych do
 * miesiaca grudzien.
 */
class Date {
    int day_;
    int hour_;
    int minute_;

public:
    /**
     * Nie mozna stworzyc daty bez podania parametrow
     */
    Date() = delete;

    /**
     * Konstruktor klasy Date. Sprawdza, czy podana data pasuje do grudnia.
     * @param day
     * @param hour
     * @param minute
     */
    explicit Date(int day, int hour, int minute);

    /**
     * Operator preinkrementacji. Zwieksza minute o 1. Sprawdza, czy data nie
     * wyszla poza grudzien.
     * @return referencja na zmodyfikowany obiekt
     */
    Date& operator++();

    /**
     * Operator porownania, porownuje przez wyliczenie minut kazdej z dat
     * @param other
     * @return this < other
     */
    bool operator<(const Date& other) const;

    /**
     * Operator odejmowania, zwraca wartosc bezwzgledna roznicy czasow w minutach
     * @param lhw - lewa wartosc
     * @param rhw - prawa wartosc
     * @return roznica czasow w minutach typu int
     */
    friend int operator-(const Date& lhv, const Date& rhv) {
        return ((lhv.day_ - rhv.day_) * 24 + (lhv.hour_ - rhv.hour_)) * 60 +
               (lhv.minute_ - rhv.minute_);
    }

    /**
     * Operator wypisania do strumienia
     * @param stream - strumien, domyslnie std::cout
     * @return December, day_, hour_:minute_
     */
    friend std::ostream& operator<<(std::ostream& stream, const Date& date) {
        std::string min = (date.minute_ < 10)
                          ? ("0" + std::to_string(date.minute_))
                          : std::to_string(date.minute_);
        return stream << "December, " << date.day_ << ", " <<
                      date.hour_ << ':' << min;
    }
};

/**
 * Funkcja zwracajaca obecna date, poczatkowo majaca wartosc 18 grudnia 16:00
 * @return obecna data
 */
Date& currentDate();

class Observer {
public:
    virtual void reaction(ChristmasTree& cht) const = 0;
};

#endif //CHRISTMASTREE_HELPER_H
