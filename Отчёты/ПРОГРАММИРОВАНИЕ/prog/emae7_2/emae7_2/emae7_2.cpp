#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int chetniy(int* A, const int n) {
	if (n == 0) { return 0; }
	return (A[n - 1] % 2 == 0) + chetniy(A, n - 1);
}
int main() {
	setlocale(LC_ALL, "RU");
	srand(time(0));
	int n, max, min;
	cout << "Введите количество элементов массива -> "; cin >> n;
	cout << "Введите максимальное значение элементов массива -> "; cin >> max;
	cout << "Введите минимальное значение элементов массива -> "; cin >> min;
	int* A = new int[n];
	cout << "\n";
	for (int i = 0; i < n; i++) {
		A[i] = rand() % (max - min + 1) + min;
		cout << A[i] << " ";
	}
	cout << "Количество чётных значений - > " << chetniy(A, n);
}