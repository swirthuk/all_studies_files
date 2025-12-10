#include <iostream>
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	int i, a;
	cout << "Enter any i: ";
	cin >> i;
	if (i < 3 && i > 0 || i == 12) {
		a = 1;
	}
	if (i >= 3 && i <= 5) {
		a = 2;
	}
	if (i > 5 && i <= 8) {
		a = 3;
	}
	if (i >= 9 && i < 12) {
		a = 4;
	}
	else {
		a = 5;
	}
	switch (a)
	{
	case 1:
		cout << "Зима";
		break;
	case 2:
		cout << "Весна";
		break;
	case 3:
		cout << "Лето";
		break;
	case 4:
		cout << "Осень";
		break;
	default:
		cout << "Вы в космосе что-ле?";
		break;
	}
}