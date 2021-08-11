/*
* Домашнее задание к уроку 6
* курса "ООП на примере С++"
* автор Недокунев А.В.
* среда разработки VSCode /компилятор MinGW/
* codepage  UTF-8
*/
#include <iostream>

using namespace std;

/*
Задание 1
Создать программу, которая считывает целое число типа int. 
И поставить «защиту от дурака»: если пользователь вводит что-то кроме одного целочисленного значения, 
нужно вывести сообщение об ошибке и предложить ввести число еще раз. Пример неправильных введенных строк:
rbtrb
nj34njkn
1n
*/
int readyInt(){
    int i = 0;
    cout << "Enter correct number <int>" << endl;
    while(!(cin>>i) || cin.get() != '\n'){
        cout << "You entered incorrect number, try again:" << endl;
            cin.clear();
            cin.sync();
    }
    return i;
}

/*
Задание 2.
Создать собственный манипулятор endll для стандартного потока вывода, который выводит два перевода строки и сбрасывает буфер.
*/

ostream& endll(ostream& os){
    os.flush();
    return (os << "\n\n");
}

////////////////////////////////////////////////////////////////////////////////////////
int main(const int argc, const char **argv){

//    cout << "You enterd correct number: " << readyInt() << endl;

    cout << "=======" << endll << "#######";
    cout;

    return 0;
}