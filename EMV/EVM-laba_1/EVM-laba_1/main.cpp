#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

union all {
	unsigned char u_char;
	long double ld;
	unsigned long long a;
};

void to_binary(unsigned long long num, long long size) {
	for (long long i = size - 1; i >= 0; i--) {
		if ((1LL << i) & num) cout << 1;
		else cout << 0;
	}
	cout << endl;
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	all num;
	int t;

	cout << "Внимание если вы введете некорректное число программа завершиться моментально!\n1.Ввести unsigned char\n2.Ввести long double\nВаш выбор: ";
	cin >> t;
	

	if (t != 1 and t != 2) return 0;// нечего фигню вводить

	if (t == 1) {
		cout << "Введите unigned char: ";
		cin >> num.u_char;
		system("cls");
		cout << "Вы ввели: " << num.u_char
			<< "\nДвоичное представление: ";
		to_binary(num.a, sizeof(num.u_char) * 8);
	}
	else {
		cout << "Введите long double: ";
		cin >> num.ld;
		system("cls");
		cout << "Вы ввели: " << num.ld
			<< "\nДвоичное представление: ";
		to_binary(num.a, sizeof(num.ld) * 8);
	}

	cout << "Внимание если вы введете некорректное число программа завершиться моментально!\nВведите количество операций: ";
	int n;
	cin >> n;
	if (n <= 0) return 0;// нечего фигню вводить

	for (int i = 0; i < n; i++) {
		int a, b;
		if (t == 1) {
			cout << "Введите номер бита(от 0 до 8) и значение которое туда надо установить(0 или 1): ";
		}
		if (t == 2) {
			cout << "Введите номер бита(от 0 до 8) и значение которое туда надо установить(0 или 1): ";
		}
		cin >> a >> b;
		if (b != 0 and b != 1) return 0;// нечего фигню вводить
		if (t == 1 and (a < 0 or a >= 8)) return 0;
		if (t == 2 and (a < 0 or a >= 64)) return 0;

		unsigned long long g = (1LL << a); // вся логика
		if (b == 1) num.a |= g;
		else num.a &= ~g;
		
		cout << "Новое значение: ";
		if (t == 1) cout << num.u_char << endl;
		if (t == 2) cout << num.ld << endl;
		cout << "Двоичное представление: ";
		if (t == 1) to_binary(num.a, sizeof(num.u_char) * 8);
		if (t == 2) to_binary(num.a, sizeof(num.ld) * 8);
	}

	return 0;
}
