#include <iostream>
using namespace std;

	double PowerN(double x, int n) {
		if (n == 0) return 1; 
		if (n > 0) return x * PowerN(x, n - 1);
		if (n < 0) return (1 / PowerN(x, -n));
}
int main() {
	setlocale(LC_ALL, "RU");
	double x; int n;
	cout << "Введите число x -> "; cin >> x;
	cout << "Введите степень n -> "; cin >> n;
	cout << "Результатом работы является -> " << PowerN(x, n);
}