/*
30.11.2020
1. Добавлен перемещающий опертор присваивания
2. В конструкторе по умолчанию (с параметром Int) запрещены неявные преобразования
3. Перемещающий конструктор и оператор присваивания - noexcept
*/
#include <iostream>

using namespace std;

class String {

public:
    char* _data;
    int _size;

    //Конструктор по умолчанию (с блокировкой неявных преобразований)
    explicit String(int nsize = 1) {
        _size = nsize;
        _data = new char[_size];

        cout << "[" << this << "]" << " - DEFAULT constructor has been called" << endl;
    }

    //Конструктор копирования
    String(const String& s) {

        //Копируем данные
        _size = s._size;
        _data = s._data;

        cout << "[" << this << "]" << " - COPY constructor has been called" << endl;        
    }

    //Конструктор перемещения
    String(String&& s) noexcept {

        //Копируем данные
        _size = s._size;
        _data = s._data;

        //Очищаем исходный объект (у которого забираем данные)
        s._data = nullptr;
        s._size = 0;

        cout << "[" << this << "]" << " - move constructor has been called" << endl;
    }

    //Копирующий оператор присваивания
    String& operator=(const String& s) {

        //Исключаем самокопирование
        if (&s == this) {
            return *this;
        }
        //Очищаем указатель
        _data = nullptr;

        //Копируем данные
        _size = s._size;
        _data = s._data;

        cout << "[" << this << "]" << " - COPY operator = has been called" << endl;

        return *this;
    }

    //Перемещающий оператор присваивания
    String& operator=(String&& s) noexcept {

        //Копируем данные
        _size = s._size;
        _data = s._data;

        //Очищаем исходный объект (у которого забираем данные)
        s._data = nullptr;
        s._size = 0;

        cout << "[" << this << "]" << " - MOVE operator = has been called" << endl;

        return *this;
    }

    //Метод вывода данных
    void print(){
        for (int i = 0; i < _size; i++) {
            cout << _data[i];
        }
        cout << endl;
    }

    //Деструктор
    ~String() noexcept {
        cout << "[" << this << "]" << " - destructor has been called for object " << endl;
        _data = nullptr;
    }
};

int main()
{
    //Сохдаем строку
    char str[] = "Hello World";

    //Создаем объект своего класса, помещаем в него строку и печаетем ее для проверки
    String mstr(12);
    mstr._data = str;
    mstr.print();

    //Проверяем конструктор копирования
    String str1 = mstr;
    mstr.print();
    str1.print();

    //Проверяем копирующий оператор присваивания
    mstr = str1;
    mstr.print();
    str1.print();

    //Проверяем перемещающий конструктор
    String str2(move(str1));
    str1.print();
    str2.print();

    //Проверяем перемещающий оператор присваивания
    str2 = move(mstr);
    mstr.print();
    str2.print();

    return 0;
}
