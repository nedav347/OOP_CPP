/*
* Домашнее задание к уроку 5
* курса "ООП на примере С++"
* автор Недокунев А.В.
* среда разработки VSCode /компилятор MinGW/
* codepage  UTF-8
*/
#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
Задание 1
Реализовать шаблон класса Pair1, который позволяет пользователю передавать данные одного типа парами.
Следующий код:
int main()
{
    Pair1<int> p1(6, 9);
    cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

    const Pair1<double> p2(3.4, 7.8);
    cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

    return 0;
}
… должен производить результат:
Pair: 6 9
Pair: 3.4 7.8
*/

template <class T>
class Pair1{
    T t1;
    T t2;
    public:
    Pair1(T value1, T value2) 
    : t1(value1), t2(value2){}
    T first() const {
        return t1;
    }
    T second() const {
        return t2;
    }
};

/*
Задание 2
Реализовать класс Pair, который позволяет использовать разные типы данных в передаваемых парах.
Следующий код:
int main()
{
    Pair<int, double> p1(6, 7.8);
    cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

    const Pair<double, int> p2(3.4, 5);
    cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

    return 0;
}
… должен производить следующий результат:
Pair: 6 7.8
Pair: 3.4 5
Подсказка: чтобы определить шаблон с использованием двух разных типов, просто разделите параметры типа шаблона запятой.
*/

template <class T1, class T2>
class Pair{
    T1 t1;
    T2 t2;
    public:
    Pair(T1 value1, T2 value2) 
    : t1(value1), t2(value2){}
    T1 first() const {
        return t1;
    }
    T2 second() const {
        return t2;
    }
};


/*
Задание 3.
Написать шаблон класса StringValuePair, в котором первое значение всегда типа string, а второе — любого типа. 
Этот шаблон класса должен наследовать частично специализированный класс Pair, в котором первый параметр — string, 
а второй — любого типа данных.
Следующий код:
int main()
{
    StringValuePair<int> svp("Amazing", 7);
    std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';
    return 0;
}
… должен производить следующий результат:
Pair: Amazing 7
Подсказка: при вызове конструктора класса Pair из конструктора класса StringValuePair не забудьте указать, 
что параметры относятся к классу Pair.
*/

template <class U>
class Pair<const string, U>{
    string s1;
    U u1;
    public:
    Pair(const string ss, U uu)
    : s1(ss), u1(uu){}
    string first() const {
        return s1;
    }
    U second() const {
        return u1;
    }

};

template <class U1>
class StringValuePair : public Pair<const string, U1>{
    public:
    StringValuePair(string str, U1 val)
    : Pair<const string, U1>(str, val){}
};

////////////////////////////////////////////////////////////////////////////////////////
int main(const int argc, const char **argv){

    Pair1<int> p1(6, 9);
    cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

    const Pair1<double> p2(3.4, 7.8);
    cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

    Pair<int, double> p3(6, 7.8);
    cout << "Pair: " << p3.first() << ' ' << p3.second() << '\n';
 
    const Pair<double, int> p4(3.4, 5);
    cout << "Pair: " << p4.first() << ' ' << p4.second() << '\n';

    StringValuePair<int> svp("Amazing", 7);
    std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';

    return 0;
}