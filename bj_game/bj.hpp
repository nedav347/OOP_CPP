#ifndef BJ_HPP
#define BJ_HPP

#include <vector>
#include <string>

using namespace std;

class Card{
    public:
    enum suit{HEARTS, DIAMONDS, CLUBS, SPADES};
    enum number{ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};
    Card(suit s, number n, bool f);
    ~Card();
    void Flip();
    int getNumber() const;
    bool getFlip() const;
    int getSuit() const;
    friend ostream& operator<<(ostream& os, const Card& aCard);
    private:
    bool flip;
    suit s1;
    number n1;
};

class Hand{
    protected:
    vector<Card*> cards;
    public:
    Hand();
    virtual ~Hand();
    void addCard(Card* c);
    void clearHand();
    int getValue() const;
};

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

class Player : public GenericPlayer{
    public:
    Player(const string& name);
    virtual bool isHitting() const;
    void Win() const;
    void Lose() const;
    void Push() const;
};

class House : public GenericPlayer{
    public:
    House(const string& name = "House");
    virtual ~House();
    virtual bool isHitting() const;
    void FlipFirstCard();
};

class Deck : public Hand{
    public:
    Deck();
    virtual ~Deck();
    void Populate();
	void Shuffle();
	void Deal (Hand& aHand);
	void AdditionalCards (GenericPlayer& aGenerlcPlayer);
};

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
