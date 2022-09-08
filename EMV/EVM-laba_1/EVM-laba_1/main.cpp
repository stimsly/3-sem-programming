#include <iostream>
#include <Windows.h>

using namespace std;

int menu() {
    cout << "1.Ввести unsigned char\n"
        << "2.Ввести long double\n"
        << "Ваш выбор: ";
    int t;
    cin >> t;
    if (t <= 0 or t > 2) {
        system("cls");
        return menu();
    }
    return t;
}

class uc {
private:
    unsigned char a;
public:
    void input() {
        cout << "Введите unsigned char: ";
        string s;
        cin >> s;
        if (s.size() >= 2) {
            system("cls");
            return input();
        }
        a = s[0];
    }
    void set(int number, int value) {
        if (value == 0) {
            int temp = 255 ^ (1 << number);
            a = char((a - 0) & temp);
        }
        else {
            a = char((a - 0) | (1 << number));
        }
    }
    void output() {
        cout << "Номер в таблице " << a - 0 << endl;
        cout << "Двоичное представление: ";
        for (int i = 7; i >= 0; i--) {
            if ((a - 0) & (1 << i)) cout << 1;
            else cout << 0;
        }
        cout << "\nСимвол - (" << a << ")" << endl;
    }
};

class ld {
private:
    long double a;
public:
    void input() {

    }
    void output() {

    }
    void set() {

    }
};

int main(){
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int t = menu();
    if (t == 1) {
        uc a;
        a.input();
        a.output();

        cout << "\nВведите количество операций: ";
        int n;
        cin >> n;

        for (int i = 0; i < n; i++) {
            cout << "Введите номер бита(0 - 7) и значение(0 или 1): ";
            int number, value;
            cin >> number >> value;

            if (number < 0 or number > 7 or value < 0 or value > 1) {
                cout << "Неверный входной формат\n";
                i--;
                continue;
            }
            
            a.set(number, value);
            a.output();
        }
    }
    else if (t == 2) {
        ld a;
        a.input();
        a.output();

        cout << "\nВведите количество операций: ";
        int n;
        cin >> n;

        for (int i = 0; i < n; i++) {
            cout << "Введите номер бита(0 - 79) и значение(0 или 1): ";
            int number, value;
            cin >> number >> value;

            if (number < 0 or number > 7 or value < 0 or value > 1) {
                cout << "Неверный входной формат\n";
                i--;
                continue;
            }

            //a.set(number, value);
            a.output();
        }
        
    }
    return 0;
}
