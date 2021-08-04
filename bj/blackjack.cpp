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
#include <string>
#include <vector>

#include "blackjack.h"

using namespace std;

/* Задание 4 к уроку 3 */
void Card::Flip(){
        flip = !flip;
    }
int Card::getNumber() const {
        return n1;
    }

/* Задание 3 к уроку 4 */
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

/*
Задание 4 к уроку 5
Согласно иерархии классов, которая представлена в методичке к уроку 3, 
от класса Hand наследует класс GenericPlayer, который обобщенно представляет игрока, 
ведь у нас будет два типа игроков - человек и компьютер. 
Создать класс GenericPlayer, в который добавить поле name - имя игрока. 
Также добавить 3 метода:
●	IsHitting() - чисто виртуальная функция, возвращает информацию, нужна ли игроку еще одна карта.
●	IsBoosted() - возвращает bool значение, есть ли у игрока перебор
●	Bust() - выводит на экран имя игрока и объявляет, что у него перебор.
*/
bool GenericPlayer::isBoosted() const{
    return (getValue() > 21);
}

void GenericPlayer::Bust() const{
    cout << m_Name << " busts" << endl;
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