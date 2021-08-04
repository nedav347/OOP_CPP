#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <vector>

using namespace std;


/* Задание 4 к уроку 3 */
class Card{
    public:
    enum suit{HEARTS = 'H', DIAMONDS = 'D', CLUBS = 'C', SPADES = 'S'};
//    enum suit{HEARTS, DIAMONDS, CLUBS, SPADES};
    enum number{TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK = 10, QUEEN = 10, KING = 10, ACE = 1};
    Card(suit s = HEARTS, number n = TEN, bool f = true)
    : s1(s), n1(n), flip(f)
    {} 
    void Flip();
    int getNumber() const;
    private:
    bool flip;
    suit s1;
    number n1;
};

/* Задание 3 к уроку 4 */
class Hand{
    vector<Card*> cards; // !!!_вектор указателей, чтобы избежать лишнего копирования (исправлено)
    public:
    Hand(){
        cards.reserve(7);
    }
    /*vitrtual*/ ~Hand(){
        clearHand();
    }
    void addCard(Card* c);
    void clearHand();
    int getValue() const;
};

/*
Задание 4 к уроку 5.
Согласно иерархии классов, которая представлена в методичке к уроку 3, 
от класса Hand наследует класс GenericPlayer, который обобщенно представляет игрока, 
ведь у нас будет два типа игроков - человек и компьютер. 
Создать класс GenericPlayer, в который добавить поле name - имя игрока. 
Также добавить 3 метода:
●	IsHitting() - чисто виртуальная функция, возвращает информацию, нужна ли игроку еще одна карта.
●	IsBoosted() - возвращает bool значение, есть ли у игрока перебор
●	Bust() - выводит на экран имя игрока и объявляет, что у него перебор.
*/

class GenericPlayer : public Hand{
    string m_Name;
    public:
    GenericPlayer(const string& name ="")
    : m_Name(name)
    {}
    virtual bool isHitting() const = 0;
    bool isBoosted() const;
    void Bust() const;
};

#endif
