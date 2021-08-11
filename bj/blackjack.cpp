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
bool Player::IsHitting() const{
    cout << m_Name << ", do you want a hit? (Y/N): ";
    char response;
    cin >> response;
    return (response == 'y' || response == 'Y');
}
void Player::Win() const
{
    cout << m_Name << " wins.\n";
}
void Player::Lose() const
{
    cout << m_Name << " loses.\n";
}
void Player::Push() const
{
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
bool House::IsHitting() const{
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

/*=============================================================================================*/
int main(const int argc, const char **argv){

    Hand h1;
    Card c1;
    Card c2;
    h1.addCard(&c1);
    h1.addCard(&c2);
    cout << h1.getValue() << endl;
 
    return 0;
}