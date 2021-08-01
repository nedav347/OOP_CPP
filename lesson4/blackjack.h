#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <vector>

using namespace std;

class Card{
    enum suit{HEARTS = 'H', DIAMONDS = 'D', CLUBS = 'C', SPADES = 'S'};
    enum number{TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK = 10, QUEEN = 10, KING = 10, ACE = 1};
    bool flip;
    suit s1;
    number n1;
    public:
    Card(suit s = HEARTS, number n = ACE)
    : s1(s), n1(n)
    {} 
    void Flip(){
        flip = !flip;
    }
    int getNumber() const {
        return n1;
    }
};

/*
Задание 3.
Реализовать класс Hand, который представляет собой коллекцию карт. 
В классе будет одно поле: вектор указателей карт (удобно использовать вектор, 
т.к. это по сути динамический массив, а тип его элементов должен быть - указатель на объекты класса Card). 
Также в классе Hand должно быть 3 метода:
●	метод Add, который добавляет в коллекцию карт новую карту, 
соответственно он принимает в качестве параметра указатель на новую карту
●	метод Clear, который очищает руку от карт
●	метод GetValue, который возвращает сумму очков карт руки (здесь предусмотреть возможность того, что туз может быть равен 11).
*/

class Hand{
    std::vector<Card> cards;
    public:
    Hand(){}
    void addCard(Card c);
    void clearHand();
    int getValue() const;
};


#endif
