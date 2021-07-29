/*
* Домашнее задание к уроку 3
* курса "ООП на примере С++"
* автор Недокунев А.В.
* среда разработки VSCode /компилятор MinGW/
* codepage UTF-8
*/
#include <iostream>
#include <cstdint>
#include <string>
using namespace std;

/*
Задание 1
Создать абстрактный класс Figure (фигура). 
Его наследниками являются классы Parallelogram (параллелограмм) и Circle (круг). 
Класс Parallelogram — базовый для классов Rectangle (прямоугольник), Square (квадрат), Rhombus (ромб). 
Для всех классов создать конструкторы. 
Для класса Figure добавить чисто виртуальную функцию area() (площадь). 
Во всех остальных классах переопределить эту функцию, исходя из геометрических формул нахождения площади.
*/

class Figure {
    public:
    virtual void area() = 0;
};

class Parallelogram : public Figure {
    string p_type;
    double p_base, p_altitude;

    public:
    Parallelogram(double base = 0, double altitude = 0)
    : p_type("Parallelogram"), p_base(base), p_altitude(altitude)
    {}
    Parallelogram(string type, double base, double altitude)
    : p_type(type), p_base(base), p_altitude(altitude)
    {}
    void setBase(double base){
        p_base = base;
    }
    void setAltitude(double altitude){
        p_altitude = altitude;
    }
    void area(){
        double a = p_base * p_altitude;
        cout << "area " << p_type << " = " << a << endl;
    }
};

class Circle : public Figure {
    double c_radius = 0;
    public:
    Circle(double r)
    : c_radius(r)
    {}
    void setRadius(double r){
        c_radius = r;
    }
    void area(){
        double a = c_radius * c_radius * 3.1415926;
        cout << "area circle = " << a << endl;
    }
};

class Rectangle : public Parallelogram {
    public:
    Rectangle(double lenth, double height)
    : Parallelogram("Rectangle", lenth, height)
    {}
};

class Square : public Parallelogram {
    public:
    Square(double lengthOfSide)
    : Parallelogram("Square", lengthOfSide, lengthOfSide)
    {}
};

class Rhombus : public Parallelogram {
    public:
    Rhombus(double base, double altitude)
    : Parallelogram("Rhombus", base, altitude)
    {}
};

/*
Задание 2
Создать класс Car (автомобиль) с полями company (компания) и model (модель). 
Классы-наследники: PassengerCar (легковой автомобиль) и Bus (автобус). 
От этих классов наследует класс Minivan (минивэн). 
Создать конструкторы для каждого из классов, чтобы они выводили данные о классах. 
Создать объекты для каждого из классов и посмотреть, в какой последовательности выполняются конструкторы. 
Обратить внимание на проблему «алмаз смерти». 
Примечание: если использовать виртуальный базовый класс, то объект самого "верхнего" базового класса создает самый "дочерний" класс.
*/

class Car{
    string c_company, c_model;
    public:
    Car(string company = "none", string model = "none")
    : c_company(company), c_model(model){
        cout << "Car" << endl;
    }
};

class PassengerCar : public virtual Car{
    public:
    PassengerCar()
    : Car("Volvo", "V70"){
        cout << "PassengerCar default" << endl;
    }
    PassengerCar(string c, string m)
    : Car(c, m){
        cout << "PassengerCar" << endl;
    }
};

class Bus : public virtual Car{
    public:
    Bus()
    : Car("Volvo", "XC70"){
        cout << "Bus default" << endl;
    }
    Bus(string c, string m)
    : Car(c, m){
        cout << "Bus" << endl;
    }
};

class Minivan : public PassengerCar, public Bus{
    public:
    Minivan()
    : Car("Volvo", "XC90"){
        cout << "Minivan default" << endl;
    }
    Minivan(string p_c, string p_m, string b_c, string b_m)
    : PassengerCar(p_c, p_m), Bus(b_c, b_m){
        cout << "Minivan" << endl;
    }

};

/*
Задание 3.
Создать класс: Fraction (дробь). 
Дробь имеет числитель и знаменатель (например, 3/7 или 9/2). (numerator, denominator)
Предусмотреть, чтобы знаменатель не был равен 0. 
Перегрузить:
●	математические бинарные операторы (+, -, *, /) для выполнения действий с дробями
●	унарный оператор (-)
●	логические операторы сравнения двух дробей (==, !=, <, >, <=, >=). 
Примечание: Поскольку операторы < и >=, > и <= — это логические противоположности, попробуйте перегрузить один через другой.
Продемонстрировать использование перегруженных операторов.
*/

class Fraction{
    double numerator, denominator;
    public:
    Fraction(int n = 0, int d = 1)
    : numerator(n), denominator(d)
    {
        if (d == 0){
            cout << "denomnator is NULL!" << endl;
            denominator = 1;
        }
    }
    Fraction operator+ (const Fraction &f) const {
        // a/b + c/d = (a*d + b* c)/(b*d)
        return Fraction(numerator * f.denominator + denominator * f.numerator, denominator * f.denominator);
    }
    Fraction operator- (const Fraction &f) const {
        // a/b - c/d = (a*d - b* c)/(b*d)
        return Fraction(numerator * f.denominator - denominator * f.numerator, denominator * f.denominator);
    }
    Fraction operator* (const Fraction &f) const {
        return Fraction(numerator * f.numerator, denominator * f.denominator);

    }
    Fraction operator/ (const Fraction &f) const {
        return Fraction(numerator * f.denominator, denominator * f.numerator);

    }
    Fraction operator- () const {
        return Fraction(-numerator, denominator);
    }
    void print(){
        cout << " " << numerator << "/" << denominator << endl;
    }
    friend bool operator== (const Fraction &lh, const Fraction &rh);
    friend bool operator!= (const Fraction &lh, const Fraction &rh);
    friend bool operator< (const Fraction &lh, const Fraction &rh);
    friend bool operator> (const Fraction &lh, const Fraction &rh);
    friend bool operator<= (const Fraction &lh, const Fraction &rh);
    friend bool operator>= (const Fraction &lh, const Fraction &rh);
};

bool operator== (const Fraction &lh, const Fraction &rh){
    if (lh.numerator * rh.denominator == rh.numerator * lh.denominator) return true;
    return false;
}
bool operator!= (const Fraction &lh, const Fraction &rh){
    return !(lh == rh);
}
bool operator< (const Fraction &lh, const Fraction &rh){
    if (lh.numerator * rh.denominator < rh.numerator * lh.denominator) return true;
    return false;
}
bool operator> (const Fraction &lh, const Fraction &rh){
    if (lh.numerator * rh.denominator > rh.numerator * lh.denominator) return true;
    return false;
}
bool operator<= (const Fraction &lh, const Fraction &rh){
    return !(lh > rh);
}
bool operator>= (const Fraction &lh, const Fraction &rh){
    return !(lh < rh);
}

/*
Задание 4.
Создать класс Card, описывающий карту в игре БлэкДжек. 
У этого класса должно быть три поля: масть, значение карты и положение карты (вверх лицом или рубашкой). 
Сделать поля масть и значение карты типом перечисления (enum). 
Положение карты - тип bool. 
Также в этом классе должно быть два метода: 
●	метод Flip(), который переворачивает карту, т.е. если она была рубашкой вверх, то он ее поворачивает лицом вверх, и наоборот.
●	метод GetValue(), который возвращает значение карты, пока можно считать, что туз = 1.
*/

class Card{
    enum suit{HEARTS = 'H', DIAMONDS = 'D', CLUBS = 'C', SPADES = 'S'};
    enum number{TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK = 10, QUEEN = 10, KING = 10, ACE = 1};
    bool flip;
    public:
    suit s1;
    number n1;
    Card(suit s = HEARTS, number n = ACE)
    : s1(s), n1(n)
    {} 
    void Flip(){
        flip = !flip;
    }
    int getNumber(){
        return n1;
    }
};

////////////////////////////////////////////////////////////////////////////////////////
int main(const int argc, const char **argv){

    Parallelogram p1(10.0, 3.0);
    p1.area();

    Circle c1(2.0);
    c1.area();

    Rectangle r1(5.0, 4.0);
    r1.area();

    Square s1(3.0);
    s1.area();

    Rhombus rh1(7.0, 4.0);
    rh1.area();

    Parallelogram p2;
    p2.area();
    p2.setBase(8.0);
    p2.setAltitude(4.0);
    p2.area();

    PassengerCar pcar1;
    Bus bcar;
    Minivan mv1;

    Fraction f1(3, 4);
    Fraction f2(2, 3);
    f1.print();
    f2.print();
    Fraction f3 = f1 + f2;
    f3.print();
    Fraction f4 = f2 - f1;
    f4.print();
    Fraction f5 = f1 * f2;
    f5.print();
    Fraction f6 = f1 / f2;
    f6.print();
    Fraction f7 = -f1;
    f7.print();
    if (f1 != f2) cout << "f1 != f2" << endl;
    cout << "f1 " << (f1 < f2 ? "<" : ">=") << " f2" << endl;

    Card card1;
    cout << "card value is " << card1.getNumber() << endl;
 
    return 0;
}