#include <iostream>
#include <cmath>
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	float a, b, result;
	cout << "Введите число а -> "; cin >> a;
	cout << "Введите число b -> "; cin >> b;
	result = pow(2, pow(a, b)) + (7.02 / (a + (a / b))) * sin(2 * a);
	cout << result;
}