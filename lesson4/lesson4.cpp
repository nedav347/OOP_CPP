/*
* Домашнее задание к уроку 4
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
#include <cassert> // для assert()

#include "blackjack.h"

using namespace std;

/*
Задание 1
Добавить в контейнерный класс, который был написан в этом уроке, методы:
●	для удаления последнего элемента массива (аналог функции pop_back() в векторах)
●	для удаления первого элемента массива (аналог pop_front() в векторах)
●	для сортировки массива
●	для вывода на экран элементов.
*/
// Код из урока - начало
class ArrayInt{
private:
    int m_length;
    int *m_data;

public:
    ArrayInt(): m_length(0), m_data(nullptr)
    { }

    ArrayInt(int length):
    m_length(length){
        assert(length >= 0);

        if (length > 0)
            m_data = new int[length];
        else
            m_data = nullptr;
    }

    ~ArrayInt(){
        delete[] m_data;
    }

    void erase(){
        delete[] m_data;

        // Здесь нам нужно указать m_data значение nullptr, чтобы на выходе не было висячего указателя
        m_data = nullptr;
        m_length = 0;
    }

    int getLength() { return m_length; }
    
    int& operator[](int index){
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }

    // Функция resize изменяет размер массива. Все существующие элементы сохраняются. Процесс медленный
    void resize(int newLength)
    {
        // Если массив уже нужной длины — return
        if (newLength == m_length)
            return;

        // Если нужно сделать массив пустым — делаем это и затем return
        if (newLength <= 0)
        {
            erase();
            return;
        }

        // Теперь знаем, что newLength >0
        // Выделяем новый массив
        int *data = new int[newLength];

        // Затем нужно разобраться с количеством копируемых элементов в новый массив
        // Нужно скопировать столько элементов, сколько их есть в меньшем из массивов
        if (m_length > 0)
        {
            int elementsToCopy = (newLength > m_length) ? m_length : newLength;

            // Поочередно копируем элементы
            for (int index=0; index < elementsToCopy ; ++index)
                data[index] = m_data[index];
        }

        // Удаляем старый массив, так как он нам уже не нужен
        delete[] m_data;

        // И используем вместо старого массива новый! Обратите внимание, m_data указывает
        // на тот же адрес, на который указывает наш новый динамически выделенный массив. Поскольку
        // данные были динамически выделенные — они не будут уничтожены, когда выйдут из области видимости
        m_data = data;
        m_length = newLength;
    }

    void insertBefore(int value, int index)
    {
        // Проверка корректности передаваемого индекса
        assert(index >= 0 && index <= m_length);

        // Создаем новый массив на один элемент больше старого массива
        int *data = new int[m_length+1];

        // Копируем все элементы до index-а
        for (int before=0; before < index; ++before)
            data[before] = m_data[before];

        // Вставляем новый элемент в новый массив
        data [index] = value;

        // Копируем все значения после вставляемого элемента
        for (int after=index; after < m_length; ++after)
            data[after+1] = m_data[after];

        // Удаляем старый массив и используем вместо него новый 
        delete[] m_data;
        m_data = data;
        ++m_length;
    }

    void push_back(int value) { insertBefore(value, m_length); }

// Код из урока - конец
// добавляем наши функции
    void del(int lenth, int front) // index - последний элемент или длина массива
    {
        // Создаем новый массив на один элемент меньше старого массива
        int *data = new int[m_length-1];

        // Копируем все элементы, за исключением первого или последнего, в зависимости от значения front
        for (int orig = front, cpy = 0;  orig < lenth + front - 1; ++orig, ++cpy)
            data[cpy] = m_data[orig];

        // Удаляем старый массив и используем вместо него новый 
        delete[] m_data;
        m_data = data;
        m_length--;
    }

    void swapInt(int *a, int *b) {
        int t = *a;
        *a = *b;
        *b = t;
    }   

    void qs(int first, int last) {
        int i = first;
        int j = last;

        int x = m_data[(first + last) / 2];

        do {
            while (m_data[i] < x) i++;
            while (m_data[j] > x) j--;

            if (i <= j) {
                swapInt(&m_data[i], &m_data[j]);
                i++;
                j--;
            }
        } while (i <= j);

        if (i < last) qs(i, last);
        if (first < j) qs(first, j);
    }


    void pop_back() { del(m_length, 0); }
    void pop_front() { del(m_length, 1); }
    void sortArray(){ qs(0, m_length); }

    void print() const {
        for (int i = 0; i < m_length; i++){
            cout << m_data[i] << ", ";
        }
    }

};

/*
Задание 2
Дан вектор чисел, требуется выяснить, сколько среди них различных. Постараться использовать максимально быстрый алгоритм.
*/
int calc(vector <int> v){
    int result = 0;
    sort(v.begin(), v.end());
    for (int i = 0; i < v.size() - 1; ++i){
        if (v[i] != v[i + 1]) result++;
    }
    return result + 1;
}

/*
Задание 3.
Реализовать класс Hand, который представляет собой коллекцию карт. 
В классе будет одно поле: вектор указателей карт (удобно использовать вектор, 
т.к. это по сути динамический массив, а тип его элементов должен быть - указатель на объекты класса Card). 
Также в классе Hand должно быть 3 метода:
●	метод Add, который добавляет в коллекцию карт новую карту, 
соответственно он принимает в качестве параметра указатель на новую карту
●	метод Clear, который очищает руку от карт
●	метод GetValue, который возвращает сумму очков карт руки (здесь предусмотреть возможность того, что туз может быть равен 11).
*/

void Hand::addCard(Card c){
    cards.push_back(c);
}

void Hand::clearHand(){
    cards.clear();
}

int Hand::getValue() const{
    int value = 0, aceCount = 0;
    for (int i = 0; i < cards.size(); ++i){
        if (cards[i].getNumber() == 1) { aceCount++; }
        value += cards[i].getNumber();
    }
    if ((aceCount > 0) && (value < 12)) { value += 10; }
    return value;
};

////////////////////////////////////////////////////////////////////////////////////////
int main(const int argc, const char **argv){
    Hand h1;
    Card c1;
    Card c2;
    h1.addCard(c1);
    h1.addCard(c2);
    cout << h1.getValue() << endl;


    return 0;
}