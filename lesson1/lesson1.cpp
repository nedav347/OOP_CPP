/*
* Домашнее задание к уроку 1
* курса "ООП на примере С++"
* автор Недокунев А.В.
* среда разработки VSCode /компилятор MinGW/
* codepage UTF-8
*/
#include <iostream>
#include <cmath>
#include <cstdint>

/*
Задание 1
Создать класс Power, который содержит два вещественных числа. 
Этот класс должен иметь две переменные-члена для хранения этих вещественных чисел. 
Еще создать два метода: один с именем set, который позволит присваивать значения переменным, 
второй — calculate, который будет выводить результат возведения первого числа в степень второго числа. 
Задать значения этих двух чисел по умолчанию.
*/

class Power {
    double number1 = 3.3;
    double number2 = 47.47;
public:
    void set (double f1, double f2){
        number1 = f1;
        number2 = f2;
    }
    double calculate () {
        return pow (number1, number2);
    }
};

/*
Задание 2
Написать класс с именем RGBA, который содержит 4 переменные-члена типа std::uint8_t: 
m_red, m_green, m_blue и m_alpha (#include cstdint для доступа к этому типу). 
Задать 0 в качестве значения по умолчанию для m_red, m_green, m_blue и 255 для m_alpha. 
Создать конструктор со списком инициализации членов, 
который позволит пользователю передавать значения для m_red, m_blue, m_green и m_alpha. 
Написать функцию print(), которая будет выводить значения переменных-членов.
std::cout.operator<<(aa);
*/

class RGBA {
    std::uint8_t m_red = 0, m_green = 0, m_blue = 0, m_alpha = 255;
    public:
    RGBA(){}
    RGBA(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
    : m_red(red), m_green(green), m_blue(blue), m_alpha(alpha) {}
    void print(){
        std::cout << "m_red = ";
        std::cout.operator<<(m_red); //uint8_t компилятор воспринимает как CHAR
        std::cout << std::endl;
        std::cout << "m_green = ";
        std::cout.operator<<(m_green);
        std::cout << std::endl;
        std::cout << "m_blue = ";
        std::cout.operator<<(m_blue); 
        std::cout << std::endl;
        std::cout << "m_alpha = ";
        std::cout.operator<<(m_alpha);
        std::cout << std::endl;
    }
};

/*
Написать класс, который реализует функциональность стека. Класс Stack должен иметь:
●	private-массив целых чисел длиной 10;
●	private целочисленное значение для отслеживания длины стека;
●	public-метод с именем reset(), который будет сбрасывать длину и все значения элементов на 0;
●	public-метод с именем push(), который будет добавлять значение в стек. 
    push() должен возвращать значение false, если массив уже заполнен, и true в противном случае;
●	public-метод с именем pop() для вытягивания и возврата значения из стека. 
    Если в стеке нет значений, то должно выводиться предупреждение;
●	public-метод с именем print(), который будет выводить все значения стека.
*/

class Stack {
    int arr[10] = {0};
    int len = 0;

    public :
    void reset(){
        len = 0;
        for (int i = 0; i < 10; ++i) {
            arr[i] = 0;
        }
    };
    int push(int n){
        if (len == 10) return false;
        arr[len] = n; //элементы в массиве нумеруются с 0, так что len соответствует следующему элементу 
        len++;
        return true;
    };
    void pop(){
        if (len == 0) {
            std::cout << "Stack is empty" << std::endl;
            return;
        }
        std::cout << arr[len - 1] << std::endl; //выводим эелемент
        len--;                                  //сдвигаем счетчик, он же указатель на следующий элемент 
        arr[len] = 0;                           //очищаем 
    };
    void print(){
        std::cout << "( ";
        for (int i = 0; i < len; ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << ")" << std::endl;
    };
};

int main(const int argc, const char **argv){
    Power test;
    std::cout << test.calculate() << std::endl; //для значений по умолчанию
    test.set(5, 3);                             //задаем значения
    std::cout << test.calculate() << std::endl; //для заданных значений

    RGBA rgba;
    rgba.print();                               //для значений по умолчанию (констуктор по умолчанию)

    RGBA rgba2(101, 102, 103, 104);
    rgba2.print();                              //для заданных пользователем значений (конструктор с параметрами)

    Stack stack;
    stack.reset();
    stack.print();
    stack.push(3);
    stack.push(7);
    stack.push(5);
    stack.print();
    
    stack.pop();
    stack.print();
    
    stack.pop();
    stack.pop();
    stack.print();
    
    return 0;
}