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

#include "bj.hpp"

using namespace std;


// класс Card - собственно карта
Card::Card(suit s = HEARTS, number n = TEN, bool f = true){ // констуктор по умолчанию (10 червей, лицом вверх)
    s1 = s;                                                 // масть
    n1 = n;                                                 // номинал
    flip = f;                                               // лицом вверх или вниз
}

Card::~Card(){}                                             // деструктор

void Card::Flip(){                                          // переворачиваем карту
    flip = !flip;
}

int Card::getNumber() const {
    return n1;
}

bool Card::getFlip() const {
    return flip;
}

int Card::getSuit() const{
    return s1;
}

ostream& operator<<(ostream& os, const Card& aCard){        // перегружаем оператор вывода
    const string NUMBERS[] = { "0", "A", "2", "3", "4", "5", "6", "7", "8", "9","10", "J", "Q", "K" };
    const string SUITS[] = { "H", "D", "C", "S" };
    
//    if (aCard.getFlip()){
//        os << NUMBERS[aCard.getNumber()] << SUITS[aCard.getSuit()];
    if (aCard.flip){                                        // функция дружественная, имеет доступ к закрытым членам класса
        os << NUMBERS[aCard.n1] << SUITS[aCard.s1];         
    } else {
        os << "XX";                                         // если лицом вниз - выводим ХХ (для второй карты дилера)
    }
    return os;
}

// класс Hand - "рука", набор карт игрока
Hand::Hand(){
    cards.reserve(7);                                       // резервируем вектор на 7 элементов
}

Hand::~Hand(){
    clearHand();
}

void Hand::addCard(Card* c){                                // добавляем карту в руку (значение в вектор)
    cards.push_back(c);
}

void Hand::clearHand(){                                     // очищаем память, просто удалить вектор нельзя
    vector<Card*>::iterator iter; // = cards.begin();
    for (iter = cards.begin(); iter != cards.end(); ++iter){
        delete *iter;
        *iter = 0;
    }
    cards.clear();
}

int Hand::getValue() const{                                 // подсчет очков у игрока
    int value = 0, aceCount = 0;
    vector<Card*>::const_iterator iter;
    for (iter = cards.begin(); iter != cards.end(); ++iter)
    {
        if ((*iter)->getNumber() == 1) { aceCount++; }
        value += (*iter)->getNumber();
    }
    if ((aceCount > 0) && (value < 12)) { value += 10; }    // туз 11 или 1?
    return value;
};

// абстрактный класс игрока (дилер тоже игрок, чтобы не городить по второму кругу для него)
GenericPlayer::GenericPlayer(const string& name =""){
    m_Name = name;
}

GenericPlayer::~GenericPlayer(){}
bool GenericPlayer::isBoosted() const{                      // проверка, нет ли перебора
    return (getValue() > 21);
}

void GenericPlayer::Bust() const{
    cout << m_Name << " busts" << endl;                     // "поздравляем" с перебором
}

ostream& operator<<(ostream& os, const GenericPlayer& gp){  //перегружаем для абстрактного игрока оператор вывода
    os << gp.m_Name << ":\t";
    vector<Card*>::const_iterator pCard;
    if (!gp.cards.empty()){
        for (pCard = gp.cards.begin(); pCard != gp.cards.end(); ++pCard){
            os << *(*pCard) << "\t";                        // складываем в выходной поток карты игрока
        }
        if (gp.getValue() != 0){
            cout << "(" << gp.getValue() << ")";            // добавляем заработанные очки
        }
    } else {
        os << "<empty>";
    }
    
    return os;
}
// класс Player - собственно игрок(и)
Player::Player(const string& name){
    m_Name = name;
}
bool Player::isHitting() const{                             // предложение взять еще карту
    cout << m_Name << ", do you want a hit? (Y/N): ";
    char response;
    cin >> response;
    return (response == 'y' || response == 'Y');
}
void Player::Win() const{                                   // выводим результат "сражения"
    cout << m_Name << " wins.\n";
}
void Player::Lose() const{
    cout << m_Name << " loses.\n";
}
void Player::Push() const{
    cout << m_Name << " pushes.\n";
}

// класс House - собственно дилер, он же крупье
House::House(const string& name){
    m_Name = "House";
}

House::~House(){}

bool House::isHitting() const{                              // дилер добирает карты пока не наберет больше 17
    return (getValue() <= 16);
}

void House::FlipFirstCard(){                                // первая карта дилера сначала закрыта
    if (!(cards.empty())){
        cards[0]->Flip();
    } else{
        cout << "No card to flip!\n";
    }
}

// класс Deck - игровой стол
Deck::Deck(){
    cards.reserve(52);
    Populate();
}

Deck::~Deck(){}

void Deck::Populate(){                                      // создаем колоду в 52 карты
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
        random_shuffle(cards.begin(), cards.end());         // тасуем колоду
}

void Deck::Deal (Hand& aHand){                              // добавляем карту игроку
    if (!cards.empty()){
        aHand.addCard(cards.back());
        cards.pop_back();
    } else {
        cout << "Out of cards. Unable to deal.";
    }
}

void Deck::AdditionalCards (GenericPlayer& gp){
    cout << endl;
    while (!(gp.isBoosted()) && gp.isHitting()){            //пока не перебрал и хочет еще - раздаем доп. карту
        Deal(gp);
        cout << gp << endl;
        if (gp.isBoosted()){                                // если перебор - "поздравляем"
            gp.Bust();
        }
    }
}

// класс Game - собственно класс самой игры
Game::Game(const vector<string>& names){
    vector<string>::const_iterator pName;
    for (pName = names.begin(); pName != names.end(); ++pName){
        players.push_back(Player(*pName));                  // создаем вектор игроков
    }
    srand(static_cast<unsigned int>(time(0)));              // ГСЧ
    m_deck.Populate();                                      // создаем колоду
    m_deck.Shuffle();                                       // тасуем колоду
}

Game::~Game(){}

void Game::play(){                                          // ИГРАЕМ!
    vector<Player>::iterator pPlayer;
    for (int i = 0; i < 2; ++i){                            // раздаем всем по 2 карты
        for (pPlayer = players.begin(); pPlayer != players.end(); ++pPlayer){
            m_deck.Deal(*pPlayer);
        }
        m_deck.Deal(m_house);
    }
    m_house.FlipFirstCard();                                // у дилера одну "прячем"
    for (pPlayer = players.begin(); pPlayer != players.end(); ++pPlayer){
        cout << *pPlayer << endl;                           // "рисуем" стол с картами игроков
    }
    cout << m_house << endl;
    for (pPlayer = players.begin(); pPlayer != players.end(); ++pPlayer){
        m_deck.AdditionalCards(*pPlayer);                   // раздаем, при желании, дополнительные карты 
    }
    m_house.FlipFirstCard();                                // открываем "секретную" карту дилера
    cout << endl << m_house;
    m_deck.AdditionalCards(m_house);                        // дилер добирает карты
    if (m_house.isBoosted()){                               // определяем победителей
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
        pPlayer->clearHand();                           // освобождаем память
    }
    m_house.clearHand();
}

/*=============================================================================================*/
int main(const int argc, const char **argv){
    int numberOfPlayers = 0;                            // переменная для количества игроков, инициализируем нулем, чтобы "войти" в цикл while
    string nameP;                                       // перерменная для задания имени игрока
    vector<string> namePlayers;                         // вектор имен игроков

    while (numberOfPlayers < 1 || numberOfPlayers > 7){
        cout << "Enter numbers of player: ";
        cin >> numberOfPlayers;                         // зададим количество игроков от 1 до 7
    }

    for (int i = 0; i < numberOfPlayers; ++i){
        cout << "Enter Name Player " << i << " : ";     // введем имена игроков
        cin >> nameP;
        namePlayers.push_back(nameP);                   // добавим имя в вектор
    }
    cout << endl;

    Game game(namePlayers);                             // создадим игру

    char repeat = 'y';                                  // переменная для ответа о повторе игры
    while (repeat != 'n' && repeat != 'N'){
        game.play();                                    // собственно сама игра
        cout << "\nRepeat Game? (Y/n): ";
        cin >> repeat;
    }

    return 0;
}