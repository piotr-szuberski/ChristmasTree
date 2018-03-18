#ifndef CHRISTMASTREE_DECORATION_H
#define CHRISTMASTREE_DECORATION_H

#include <iostream>
#include <list>
#include <memory>
#include "helper.h"
#include "person.h"

/**
 * Abstrakcyjna klasa dekoracji
 */
class Decoration {
protected:
    std::string name_;
    Price price_;

public:
    /**
     * Nie mozna stworzyc dekoracji bez parametrow
     */
    Decoration() = delete;

    /**
     * Konstruktor klasy Decoration
     * @param name - przekazywany przez wartosc, a nastepnie przypisywany
     * jako rvalue przez std::move()
     * @param price
     */
    explicit Decoration(std::string name, const Price& price)
            : name_(std::move(name)), price_(price) {}

    /**
     * Getter nazwy dekoracji
     * @return kopia nazwy
     */
    std::string getName() const;

    /**
     * Getter ceny dekoracji
     * @return kopia ceny
     */
    Price getPrice() const;

    /**
     * Wirtualna metoda doOperation
     */
    virtual void doOperation(std::ostream&) = 0;

    /**
     * Wirtualny destruktor, aby mogl zostac wywolany destruktor w ChristmasTree
     * w przypadku Decoration* dec = new ChristmasTree(...)
     */
     virtual ~Decoration() = default;
};

/**
 * Abstrakcyjna klasa lisc, ktory moze byc elementem kompozytu
 */
class Leaf : public Decoration {

public:
    explicit Leaf(std::string name, const Price& price)
            : Decoration(std::move(name), price) {}
};

/**
 * Klasa bombki choinkowej dziedziczaca po Decoration
 */
class GlassBall : public Leaf {
    bool broken_ = false;

public:
    /**
     * Konstruktor bombki choinkowej
     * @param name
     * @param price
     */
    GlassBall(std::string name, const Price& price)
            : Leaf(std::move(name), price) {}

    /**
     * Z prawdopodobienstwem 25% zmienia stan broken_ na true i wypisuje napis
     * "name_: broken_" na strumien wyjscia
     * @param os strumien wyjscia
     */
    void doOperation(std::ostream&) override;
};

/**
 * Klasa swiatelek choinkowych dziedziczaca po Decoration
 * state_: -1 = wylaczone, 0 - stale, 1 - migoczace
 */
class Lights : public Leaf {
    int state_ = -1;

public:
    /**
     * Konstruktor swiatelek choinkowych
     * @param name
     * @param price
     */
    explicit Lights(std::string name, const Price& price)
            : Leaf(std::move(name), price) {}

    /**
     * Cyklicznie zmienia stan swiatelek i wypisuje napis
     * "name_: state_" na strumien wyjscia
     * @param os strumien wyjscia
     */
    void doOperation(std::ostream&) override;
};

/**
 * Klasa drzewek choinkowych (nie sztucznych) dziedziczaca po Decoration
 * posiada dodatkowe pola:
 * coverage_ - pokrycie iglami, o wartosciach calkowitych z przedzialu [0, 100]
 * cut_time_ - data sciecia drzewka
 * the_time_ - pomocnicza zmienna dla okreslenia zawartosci procentowej igiel
 * drzewka
 */
class Tree : public Leaf {
    int coverage_ = 100;
    Date cut_time_;
    int the_time_;

public:
    /**
     * Konstruktor klasy Tree
     * @param name
     * @param price
     * @param date
     */
    Tree(std::string name, const Price& price, const Date& date);

    /**
     * Wypisuje na wyjscie informacje, jaki procent igiel pozostal drzewku.
     * Igly opadaja liniowo od momentu sciecia do konca grudnia. W symulacji
     * tej niezaleznie od daty sciecia ostatniego dnia grudnia minute przed
     * polnoca drzewko traci ostatnia igle.
     * @param os - strumien wyjscia
     */
    void doOperation(std::ostream&) override;
};

/**
 * Klasa ChristmasTree - kompozyt. Zawiera w sobie liscie (inne dekoracje)
 * oraz obserwatorow, ktorym wysyla informacje o zmianie w strukturze kompozytu
 */
class ChristmasTree : public Decoration {
    std::list<std::shared_ptr<Decoration>> decorations_;
    std::list<std::shared_ptr<Person>> observers_;

public:
    /**
     * Konstruktor kompozytu
     * @param name
     */
    explicit ChristmasTree(std::string name) : Decoration(std::move(name), Price{0}) {}

    /**
     * Wykonuje funkcje doOperation na kazdym obiekcie z listy
     * @param os - strumien wyjscia
     */
    void doOperation(std::ostream& os) override;

    /**
     * Dodaje wskaznik na obiekt typu Decoration i zwieksza pole price_ kompozytu
     */
    void addDecoration(std::shared_ptr<Decoration>);

    /**
     * Usuwa dekoracje, ale nie obniza ceny kompozytu, bo calkowity koszt jaki
     * rodzina wydala nie zwraca sie
     */
    void removeDecoration(std::list<std::shared_ptr<Decoration>>::iterator);

    /**
     * Zwraca iterator na poczatek listy dekoracji
     * @return decoration_iterator = begin()
     */
    std::list<std::shared_ptr<Decoration>>::iterator begin();

    /**
     * Zwraca iterator na koniec listy dekoracji
     * @return decoration_iterator = end()
     */
    std::list<std::shared_ptr<Decoration>>::iterator end();

    /**
     * Dodaje obserwatora do listy obserwatorow
     */
    void attachObserver(std::shared_ptr<Person>);

    /**
     * Usuwa obserwatora z listy obserwatorow
     */
    void detachObserver(std::shared_ptr<Person>);

    /**
     * Iteruje przez wszystkich obserwatorow i wywoluje na nich funkcje reaction()
     */
    void notify();
};

#endif //CHRISTMASTREE_DECORATION_H
