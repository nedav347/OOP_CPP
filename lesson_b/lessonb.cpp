/*
* Домашнее задание к уроку 2
* курса "ООП на примере С++"
* автор Недокунев А.В.
* среда разработки VSCode /компилятор MinGW/
* codepage UTF-8
*/
#include <iostream>
#include <cmath>
#include <cstdint>
#include <string>
using namespace std;

/*
Задание 1
Создать класс Person (человек) с полями: имя, возраст, пол и вес. 
Определить методы переназначения имени, изменения возраста и веса. 
Создать производный класс Student (студент), имеющий поле года обучения. 
Определить методы переназначения и увеличения этого значения. 
Создать счетчик количества созданных студентов. 
В функции main() создать несколько студентов. По запросу вывести определенного человека.
*/

class Person {
    string m_name;
    int m_age;
    char m_gender;
    int m_weight;
    public:
    Person(string name = "", int age = 0, char gender = ' ', int weight = 0)
    : m_name(name), m_age(age), m_gender(gender), m_weight(weight) {}
    void setName(string n){
        m_name = n;
    }
    void setAge(int a){
        m_age = a;
    }
    void setGender(char g){
        m_gender = g;
    }
    int setWeight(int w){
        m_weight = w;
    }
    string getName(){
        return m_name;
    }
    int getAge(){
        return m_age;
    }
    char getGender(){
        return m_gender;
    }
    int getWeight(){
        return m_weight;
    }
};

class Student : public Person {
    int m_year;
    public:
    static int count; //а вот и счетчик студентов, т.к. Static - общие для всех обектов класса...
    Student(int year = 0)
    : m_year(year) {
        count++;
    }
    ~Student(){
        count--;
    }
    void incrementYear (){
        m_year++;
    }
    void setYear(int y){
        m_year = y;
    }
    int getYear(){
        return m_year;
    }
};

int Student::count = 0;

/*
Задание 2
Создать классы Apple (яблоко) и Banana (банан), которые наследуют класс Fruit (фрукт). 
У Fruit есть две переменные-члена: name (имя) и color (цвет). 
Добавить новый класс GrannySmith, который наследует класс Apple.
*/

class Fruit{
    string m_name;
    string m_color;
    public:
    Fruit(string name, string color)
    : m_name(name), m_color(color){}
    string getName(){
        return m_name;
    }
    string getColor(){
        return m_color;
    }
};

class Apple : public Fruit{
    public:
    Apple()
    : Fruit("apple", "rose")
    {}
    Apple(string color)
    : Fruit("apple", color)
    {}
    Apple(string name, string color)
    : Fruit(name, color)
    {}
};

class Banana : public Fruit{
    public:
    Banana(string name = "banana", string color = "yellow")
    : Fruit(name, color){}
};

class GrannySmith : public Apple{
    public:
    GrannySmith(string color = "green")
    : Apple("Granny Smith apple", color)
    {}
};

/*
Изучить правила игры в Blackjack. 
Подумать, как написать данную игру на С++, используя объектно-ориентированное программирование. 
Сколько будет классов в программе? Какие классы будут базовыми, а какие производными? 
Продумать реализацию игры с помощью классов и записать результаты.
*/

/*
Класс Game - базовый, основной класс игры.
Класс Deck - базовый, стол, на нем будет массив карт (вектор).
Класс Card - базовый, собственно карты.
Класс Hand - базовый, набор карт игрока.
Класс Player - производный от Hand, игроки.
Класс Dealer - производный от Hand, крупье.
Класс Stat - базовый, сбор игровой статистики.
*/

#include <vector>

class Game{
    Player player;
    Dealer dealer;
    Deck deck;
    Stat s;
    public: //здесь будуе некоторые функции
    char compareSum();
    bool checkWins();
    char checkEnd();
    bool startBet();
    bool startGame();
    void printStatistics();
    void printInstructions();
    //..
};

class Deck{
    std::vector<Card> deck;
    public:
    void initDeck();
    //..
};

class Card{
    int number;
    char suit;
    public: 
    void setNumber(int no);
    void setSuit(char c);
    int getNumber();
    char getSuit();
    void printCard();
    //..
};

class Hand{
    std::vector<Card> hand;
    int sum;
    public:
    int getSum();
    void addCard(Card c);
    void printCards();
    //..
};

class Player: public Hand{
    std::string name;
    int cash, bet;
    int wins, loses;
    public:
    std::string getName();
    void setName(std::string nm);
    void setBet(int b);
    void addCash(int c);
    void incrementWins();
    void incrementLoses();
    int getBet();
    int getCash();
    int getWins();
    int getLoses();
    //..
};

class Dealer: public Hand{
    public:
    void printCard();
};

class Stat{
    private:
    std::string name;
    int cash, wins, loses;
    public:
    void setName(std::string nm);
    void setCash(int c);
    void setWins(int w);
    void setLoses(int l);
    std::string getName();
    int getCash();
    int getWins();
    int getLoses();
    //..
};


////////////////////////////////////////////////////////////////////////////////////////
int main(const int argc, const char **argv){
    Apple a("red");
    Banana b;
    GrannySmith c;

    std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
    std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
    std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";
/*
My apple is red.
My banana is yellow.
My Granny Smith apple is green.
*/    
    Student Ivanov;
    cout << Ivanov.count << endl;
    Student Petrova;
    cout << Petrova.count << endl;
    Student Sidorov;
    cout << Sidorov.count << endl;
    Ivanov.setAge(18);
    Ivanov.setGender('M');
    Ivanov.setName("Anton");
    Ivanov.setWeight(75);
    Ivanov.setYear(1);
    Petrova.setAge(19);
    Petrova.setGender('F');
    Petrova.setName("Hannah");
    Petrova.setWeight(65);
    Petrova.setYear(2);
    Sidorov.setAge(20);
    Sidorov.setGender('M');
    Sidorov.setName("Ivan");
    Sidorov.setWeight(85);
    Sidorov.setYear(3);

    cout << "Student Petrova:\nName: " << Petrova.getName() << endl;
    cout << "Age: " << Petrova.getAge() << endl;
    cout << "Gender: " << Petrova.getGender() << endl;
    cout << "Weight: " << Petrova.getWeight() << endl;
    cout << "Year: " << Petrova.getYear() << endl;

    Petrova.incrementYear();
    cout << "Year: " << Petrova.getYear() << endl;

    return 0;
}