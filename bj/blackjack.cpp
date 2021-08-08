/*
* Домашнее задание к урокам
* курса "ООП на примере С++"
* по созданию игры BlackJack.
* автор Недокунев А.В.
* среда разработки VSCode /компилятор MinGW/
* codepage  UTF-8
*/
#include <iostream>
#include <cstdint>
//#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

#include "blackjack.hpp"

using namespace std;

/* Задание 4 к уроку 3 */
Card::Card(suit s = HEARTS, number n = TEN, bool f = true){
    s1 = s;
    n1 = n;
    flip = f;
}
void Card::Flip(){
    flip = !flip;
}
int Card::getNumber() const {
    return n1;
}


/* Задание 3 к уроку 4 */
Hand::Hand(){
    cards.reserve(7);
}
/*vitrtual*/ Hand::~Hand(){
    clearHand();
}

void Hand::addCard(Card* c){
    cards.push_back(c);
}

void Hand::clearHand(){  // !!!_метод Clear реализован неверно. Необходимо не забывать про освобождение динамически выделенной памяти.
    vector<Card*>::iterator iter = cards.begin();
    for (iter = cards.begin(); iter != cards.end(); ++iter){
        delete *iter;
        *iter = 0;
    }
    cards.clear();
}

int Hand::getValue() const{
    int value = 0, aceCount = 0;
    vector<Card*>::const_iterator iter;
    for (iter = cards.begin(); iter != cards.end(); ++iter)
    {
        if ((*iter)->getNumber() == 1) { aceCount++; }
        value += (*iter)->getNumber();
    }
    if ((aceCount > 0) && (value < 12)) { value += 10; }
    return value;
};

/* Задание 4 к уроку 5 */
GenericPlayer::GenericPlayer(const string& name =""){
    m_Name = name;
}
GenericPlayer::~GenericPlayer(){}
bool GenericPlayer::isBoosted() const{
    return (getValue() > 21);
}
void GenericPlayer::Bust() const{
    cout << m_Name << " busts" << endl;
}

/*
Задание 3 к уроку 6.	
Реализовать класс Player, который наследует от класса GenericPlayer. У этого класса будет 4 метода:
●	virtual bool IsHitting() const - реализация чисто виртуальной функции базового класса. Метод спрашивает у пользователя, нужна ли ему еще одна карта и возвращает ответ пользователя в виде true или false. 
●	void Win() const - выводит на экран имя игрока и сообщение, что он выиграл.
●	void Lose() const - выводит на экран имя игрока и сообщение, что он проиграл.
●	void Push() const - выводит на экран имя игрока и сообщение, что он сыграл вничью.
*/
Player::Player(const string& name){
    m_Name = name;
}
bool Player::isHitting() const{
    cout << m_Name << ", do you want a hit? (Y/N): ";
    char response;
    cin >> response;
    return (response == 'y' || response == 'Y');
}
void Player::Win() const{
    cout << m_Name << " wins.\n";
}
void Player::Lose() const{
    cout << m_Name << " loses.\n";
}
void Player::Push() const{
    cout << m_Name << " pushes.\n";
}

/*
Задание 4  к уроку 6.
Реализовать класс House, который представляет дилера. Этот класс наследует от класса GenericPlayer. У него есть 2 метода:
●	virtual bool IsHitting() const - метод указывает, нужна ли дилеру еще одна карта. Если у дилера не больше 16 очков, то он берет еще одну карту.
●	void FlipFirstCard() - метод переворачивает первую карту дилера.
*/
House::House(const string& name){
    m_Name = "House";
}
House::~House(){}
bool House::isHitting() const{
    return (getValue() <= 16);
}
void House::FlipFirstCard(){
    if (!(cards.empty())){
        cards[0]->Flip();
    } else{
        cout << "No card to flip!\n";
    }
}

/*
Задание 5  к уроку 6.
Написать перегрузку оператора вывода для класса Card. 
Если карта перевернута рубашкой вверх (мы ее не видим), вывести ХХ, 
если мы ее видим, вывести масть и номинал карты. 
Также для класса GenericPlayer написать перегрузку оператора вывода, 
который должен отображать имя игрока и его карты, а также общую сумму очков его карт.
*/
ostream& operator<<(ostream& os, const Card& aCard)
{
    const string NUMBERS[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9","10", "J", "Q", "K" };
    const string SUITS[] = { "H", "D", "C", "S" };
    
    if (aCard.flip){
        os << NUMBERS[aCard.n1] << SUITS[aCard.s1];
    } else {
        os << "XX";
    }
    
    return os;
}
ostream& operator<<(ostream& os, const GenericPlayer& gp){
    os << gp.m_Name << ":\t";
    vector<Card*>::const_iterator pCard;
    if (!gp.cards.empty()){
        for (pCard = gp.cards.begin(); pCard != gp.cards.end(); ++pCard){
            os << *(*pCard) << "\t";
        }
        if (gp.getValue() != 0){
            cout << "(" << gp.getValue() << ")";
        }
    } else {
        os << "<empty>";
    }
    
    return os;
}

/*
Задание 3 к уроку 7.
Создать класс Deck, который наследует от класса Hand и представляет собой колоду карт. Класс Deck имеет 4 метода:
●	vold Populate() - Создает стандартную колоду из 52 карт, вызывается из конструктора.
●	void Shuffle() - Метод, который тасует карты, можно использовать функцию из алгоритмов STL random_shuffle
●	vold Deal (Hand& aHand) - метод, который раздает в руку одну карту
●	void AddltionalCards (GenericPlayer& aGenerlcPlayer) - раздает игроку дополнительные карты до тех пор, пока он может и хочет их получать
Обратите внимание на применение полиморфизма. В каких методах применяется этот принцип ООП?
*/
Deck::Deck(){
    cards.reserve(52);
    Populate();
}
Deck::~Deck(){}
void Deck::Populate(){
    clearHand();
    for (int s = Card::HEARTS; s <= Card::SPADES; ++s)
    {
        for (int n = Card::ACE; n <= Card::KING; ++n)
        {
            addCard(new Card(static_cast<Card::suit>(s), static_cast<Card::number>(n)));
        }
    }
}
void Deck::Shuffle(){
        random_shuffle(cards.begin(), cards.end());
}
void Deck::Deal (Hand& aHand){
    if (!cards.empty())
    {
        aHand.addCard(cards.back());
        cards.pop_back();
    }
    else
    {
        cout << "Out of cards. Unable to deal.";
    }

}
void Deck::AddltionalCards (GenericPlayer& gp){
    cout << endl;
    while (!(gp.isBoosted()) && gp.isHitting())
    {
        Deal(gp);
        cout << gp << endl;
        
        if (gp.isBoosted())
        {
            gp.Bust();
        }
    }
}
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
Game::Game(const vector<string>& names){
    vector<string>::const_iterator pName;
    for (pName = names.begin(); pName != names.end(); ++pName){
        players.push_back(Player(*pName));
    }
    srand(static_cast<unsigned int>(time(0)));
    m_deck.Populate();
    m_deck.Shuffle();
}

Game::~Game(){}

void Game::play()
{
    vector<Player>::iterator pPlayer;
    for (int i = 0; i < 2; ++i){
        for (pPlayer = players.begin(); pPlayer != players.end(); ++pPlayer){
            m_deck.Deal(*pPlayer);
        }
        m_deck.Deal(m_house);
    }
    m_house.FlipFirstCard();
    for (pPlayer = players.begin(); pPlayer != players.end(); ++pPlayer){
        cout << *pPlayer << endl;
    }
    cout << m_house << endl;
    for (pPlayer = players.begin(); pPlayer != players.end(); ++pPlayer){
        m_deck.AddltionalCards(*pPlayer);
    }
    m_house.FlipFirstCard();
    cout << endl << m_house;
    m_deck.AddltionalCards(m_house);
    if (m_house.isBoosted()){
        for (pPlayer = players.begin(); pPlayer != players.end(); ++pPlayer){
            if (!(pPlayer->isBoosted())){
                pPlayer->Win();
            }
        }
    } else {
        for (pPlayer = players.begin(); pPlayer != players.end(); ++pPlayer){
            if (!(pPlayer->isBoosted())){
                if (pPlayer->getValue() > m_house.getValue()){
                    pPlayer->Win();
                } else if (pPlayer->getValue() < m_house.getValue()) {
                    pPlayer->Lose();
                } else {
                    pPlayer->Push();
                }
            }
        }
        
    }
    for (pPlayer = players.begin(); pPlayer != players.end(); ++pPlayer){
        pPlayer->clearHand();
    }
    m_house.clearHand();
}

/*
Задание 5 к уроку 7.
Написать функцию main() к игре Блекджек. 
В этой функции вводятся имена игроков. 
Создается объект класса Game и запускается игровой процесс. 
Предусмотреть возможность повторной игры.
*/

/*=============================================================================================*/
int main(const int argc, const char **argv){
    int numberOfPlayers = 0;
    string nameP;
    vector<string> namePlayers;
    while (numberOfPlayers < 1 || numberOfPlayers > 7){
        cout << "Enter numbers of player: ";
        cin >> numberOfPlayers;
    }
    for (int i = 0; i < numberOfPlayers; ++i){
        cout << "Enter Name Player " << i << " : ";
        cin >> nameP;
        namePlayers.push_back(nameP);
    }
    cout << endl;

    Game game(namePlayers);
    char repeat = 'y';
    while (repeat != 'n' && repeat != 'N'){
        game.play();
        cout << "\nRepeat Game? (Y/n): ";
        cin >> repeat;
    }

    return 0;
}