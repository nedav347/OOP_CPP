/*
* Домашнее задание к уроку 7
* курса "ООП на примере С++"
* автор Недокунев А.В.
* среда разработки VSCode /компилятор MinGW/
* codepage  UTF-8
*/
#include <iostream>
#include <memory>
#include <ctime>

using namespace std;

/*
Задание 1
Создайте класс Date с полями день, месяц, год и методами доступа к этим полям. 
Перегрузите оператор вывода для данного класса. 
Создайте два "умных" указателя today и date. 
Первому присвойте значение сегодняшней даты. 
Для него вызовите по отдельности методы доступа к полям класса Date, 
а также выведите на экран данные всего объекта с помощью перегруженного оператора вывода. 
Затем переместите ресурс, которым владеет указатель today в указатель date. 
Проверьте, являются ли нулевыми указатели today и date и выведите соответствующую информацию об этом в консоль.
*/
class Date{
    int Day, Month, Year;
    public:
    Date();
    Date(int d1, int m1, int y1);
    friend ostream& operator<<(ostream& out, const Date &date);
    void setDay(int d);
    void setMonth(int m);
    void setYear(int y);
    int getDay() const;
    int getMonth() const;
    int getYear() const;
     
};

Date::Date(){
    Day = 0;
    Month = 0;
    Year = 0;
}

Date::Date(int d1, int m1, int y1){
    Day = d1;
    Month = m1;
    Year = y1;
}

ostream& operator<< (ostream& out, const Date &date){
    out << "Date: " << date.getDay() << "." << date.getMonth() << "." << date.getYear() << endl;
    return out;
}

void Date::setDay(int d){
    Day = d;
}
void Date::setMonth(int m){
    Month = m;
}
void Date::setYear(int y){
    Year = y;
}
int Date::getDay() const{
    return Day;
}
int Date::getMonth() const{
    return Month;
}
int Date::getYear() const{
    return Year;
}


/*
Задание 2 
По условию предыдущей задачи создайте два умных указателя date1 и date2. 
●	Создайте функцию, которая принимает в качестве параметра два умных указателя типа Date и сравнивает их между собой 
(сравнение происходит по датам). Функция должна вернуть более позднюю дату.
●	Создайте функцию, которая обменивает ресурсами (датами) два умных указателя, переданных в функцию в качестве параметров.
Примечание: обратите внимание, что первая функция не должна уничтожать объекты, переданные ей в качестве параметров.
*/

Date *compareDate(Date *d1, Date *d2){
    int day1, month1, year1, day2, month2, year2;
    day1 = d1->getDay();
    day2 = d2->getDay();
    month1 = d1->getMonth();
    month2 = d2->getMonth();
    year1 = d1->getYear();
    year2 = d2->getYear();
    
    if (year1 != year2) return  year1 > year2 ? d1 : d2;
    if (month1 != month2) return month1 > month2 ? d1 : d2;
    if (day1 != day2) return day1 > day2 ? d1 : d2;
}

void exchangeDate(unique_ptr<Date> d1, unique_ptr<Date> d2){
    unique_ptr<Date> tmp = make_unique<Date>();
    cout << "d1 " << *d1 << endl;
    cout << "d2 " << *d2 << endl;
    tmp = move(d1);
    d1 = move(d2);
    d2 = move (tmp);
    cout << "d1 " << *d1 << endl;
    cout << "d2 " << *d2 << endl;

}
////////////////////////////////////////////////////////////////////////////////////////
int main(const int argc, const char **argv){

    unique_ptr<Date> today = make_unique<Date>();

    time_t t = time(0);
    tm * local = localtime(&t);

    today->setDay(local->tm_mday); 
    today->setMonth(local->tm_mon);
    today->setYear(local->tm_year + 1900);

    cout << "today " << *today << endl;

    unique_ptr<Date> date = make_unique<Date>();

	cout << "today is " << (static_cast<bool>(today) ? "not null\n" : "null\n");
	cout << "date is " << (static_cast<bool>(date) ? "not null\n" : "null\n");

    date = move(today);

    cout << "date " << *date << endl;

	cout << "today is " << (static_cast<bool>(today) ? "not null\n" : "null\n");
	cout << "date is " << (static_cast<bool>(date) ? "not null\n" : "null\n");

    unique_ptr<Date> date1(new Date(12, 3, 1969));
    unique_ptr<Date> date2(new Date(9, 2, 1971));

    cout << "last date is " << *compareDate(date1.get(), date2.get()) << endl;

    exchangeDate(move(date1), move(date2));

    return 0;
}