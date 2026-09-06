#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	int a, b;
	cout << "Введите целое значение для a -> "; cin >> a;
	cout << "Введите целое знчение для b -> "; cin >> b;
	cout << "Первоначальные значения: " << a << setw(4) << b << endl;
	int* c = &a;
	int* d = &b;
	int x = *c;
	a = *d;
	b = x;
	cout << "Поменянные местами: " << a << setw(4) << b;
}