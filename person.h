#ifndef CHRISTMASTREE_PERSON_H
#define CHRISTMASTREE_PERSON_H

#include "helper.h"
#include "decoration.h"

/**
 * Klasa abstrakcyjna Person, zawiera pole imie oraz
 * implementuje metode getName()
 */
class Person : public Observer {
protected:
    std::string name_;

public:
    /**
     * Nie mozna stworzyc osoby bez parametrow
     */
    Person() = delete;

    /**
     * Konstruktor klasy Person
     * @param name - przekazywany przez wartosc i nastepnie jako rvalue przez
     * std::move
     */
    explicit Person(std::string name) : name_(std::move(name)) {}

    /**
     * getter klasy Person
     * @return stala referencja na name_
     */
    const std::string& getName() const;

    /**
     * Funkcja abstrakcyjna pochodzaca od Observer
     * @param price
     */
    virtual void reaction(ChristmasTree& price) const override = 0;
};

/**
 * Pochodna klasy osoba. Dorosly posiada pieniadze i moze kupowac dekoracje
 */
class Adult : public Person {
private:
    Price savings_{0};

public:
    /**
     * Konstruktor klasy Adult.
     * @param name
     * @param price domyslnie ustawiony na 0
     */
    explicit Adult(std::string name, const Price& price = Price{0})
            : Person(std::move(name)), savings_(price) {}

    /**
     * Kupuje dekoracje, odejmujac od posiadanych pieniedzy jej koszt
     */
    void buyDecoration(const Decoration&);

    /**
     * Zwraca posiadane oszczednosci
     * @return oszczednosci
     */
    const Price& getSavings() const;

    /**
     * Reakcja na zmiane w kompozycie w formacie
     * "We have new decoration!\nTotal cost is n PLN.\n"
     * @param price - dorosla osoba potrzebuje wiedziec ile kompozyt kosztowal
     */
    void reaction(ChristmasTree& cht) const override;
};

/**
 * Klasa Child, dziedziczy po Person
 */
class Child : public Person {
public:
    /**
     * Konstruktor klasy Child
     * @param name
     */
    explicit Child(std::string name) : Person(std::move(name)) {}

    /**
     * Reakcja na zmiane w kompozycie w formacie
     * "Wow!"
     * Wywoluje doOperation na ostatnio dodanym obiekcie do kompozytu
     * @param price
     */
    void reaction(ChristmasTree& price) const override;
};

#endif //CHRISTMASTREE_PERSON_H
