#ifndef BLACKJACK_HPP
#define BLACKJACK_HPP

#include <vector>
#include <string>

using namespace std;


/* Задание 4 к уроку 3 */
class Card{
    public:
    enum suit{HEARTS, DIAMONDS, CLUBS, SPADES};
    enum number{ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};
    Card(suit s, number n, bool f);
    void Flip();
    int getNumber() const;
    friend ostream& operator<<(ostream& os, const Card& aCard);
    private:
    bool flip;
    suit s1;
    number n1;
};

/* Задание 3 к уроку 4 */
class Hand{
    protected:
    vector<Card*> cards; // !!!_вектор указателей, чтобы избежать лишнего копирования (исправлено)
    public:
    Hand();
    /*vitrtual*/ ~Hand();
    void addCard(Card* c);
    void clearHand();
    int getValue() const;
};

/*
Задание 4 к уроку 5.
*/
class GenericPlayer : public Hand{
    protected:
    string m_Name;
    friend ostream& operator<<(ostream& os, const GenericPlayer& aGenericPlayer);
    public:
    GenericPlayer(const string& name);
//    virual ~GenericPlayer();
    virtual bool isHitting() const = 0;
    bool isBoosted() const;
    void Bust() const;
};

/*
Задание 3 к уроку 6.	
Реализовать класс Player, который наследует от класса GenericPlayer. У этого класса будет 4 метода:
●	virtual bool IsHitting() const - реализация чисто виртуальной функции базового класса. Метод спрашивает у пользователя, нужна ли ему еще одна карта и возвращает ответ пользователя в виде true или false. 
●	void Win() const - выводит на экран имя игрока и сообщение, что он выиграл.
●	void Lose() const - выводит на экран имя игрока и сообщение, что он проиграл.
●	void Push() const - выводит на экран имя игрока и сообщение, что он сыграл вничью.
*/
class Player : public GenericPlayer{
    public:
    Player(const string& name);
    virtual bool IsHitting() const;
    void Win() const;
    void Lose() const;
    void Push() const;
};

/*
Задание 4  к уроку 6.
Реализовать класс House, который представляет дилера. Этот класс наследует от класса GenericPlayer. У него есть 2 метода:
●	virtual bool IsHitting() const - метод указывает, нужна ли дилеру еще одна карта. Если у дилера не больше 16 очков, то он берет еще одну карту.
●	void FlipFirstCard() - метод переворачивает первую карту дилера.
*/
class House : public GenericPlayer{
    public:
    House(const string& name = "House");
    virtual ~House();
    virtual bool IsHitting() const;
    void FlipFirstCard();
};

#endif
