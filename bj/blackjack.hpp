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
    virtual ~Hand();
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
    virtual ~GenericPlayer();
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
    virtual bool isHitting() const;
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
    virtual bool isHitting() const;
    void FlipFirstCard();
};

/*
Задание 3 к уроку 7.
Создать класс Deck, который наследует от класса Hand и представляет собой колоду карт. Класс Deck имеет 4 метода:
●	vold Populate() - Создает стандартную колоду из 52 карт, вызывается из конструктора.
●	void Shuffle() - Метод, который тасует карты, можно использовать функцию из алгоритмов STL random_shuffle
●	vold Deal (Hand& aHand) - метод, который раздает в руку одну карту
●	void AddltionalCards (GenericPlayer& aGenerlcPlayer) - раздает игроку дополнительные карты до тех пор, пока он может и хочет их получать
Обратите внимание на применение полиморфизма. В каких методах применяется этот принцип ООП?
*/
class Deck : public Hand{
    public:
    Deck();
    virtual ~Deck();
    void Populate();
	void Shuffle();
	void Deal (Hand& aHand);
	void AddltionalCards (GenericPlayer& aGenerlcPlayer);
};

/*
Задание 4 к уроку 7. 
Реализовать класс Game, который представляет собой основной процесс игры. У этого класса будет 3 поля:
●	колода карт
●	рука дилера
●	вектор игроков.
Конструктор класса принимает в качестве параметра вектор имен игроков и создает объекты самих игроков. 
В конструкторе создается колода карт и затем перемешивается. 
Также класс имеет один метод play(). 
В этом методе раздаются каждому игроку по две стартовые карты, а первая карта дилера прячется. 
Далее выводится на экран информация о картах каждого игра, в т.ч. и для дилера. 
Затем раздаются игрокам дополнительные карты. 
Потом показывается первая карта дилера и дилер набирает карты, если ему надо. 
После этого выводится сообщение, кто победил, а кто проиграл. 
В конце руки всех игроков очищаются.
*/
class Game{
    Deck m_deck;
    House m_house;
    vector<Player> players;
    public:
    Game(const vector<string>& names);
    ~Game();
    void play();
};

#endif
