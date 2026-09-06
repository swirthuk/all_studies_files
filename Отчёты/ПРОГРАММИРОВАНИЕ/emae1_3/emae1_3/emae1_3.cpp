#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;
int ex2(const int max, const int min) {
	int m[8][8];
	int maxi = -100;
	int ans = 0;
	cout << "\nМатрица:\n";
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			m[i][j] = rand() % (max - min + 1) + min;
			cout << m[i][j] << " ";
			if (m[i][j] > maxi) { maxi = m[i][j]; }
		}
		cout << endl;
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (m[i][j] = maxi) { ans = i; }
		}
		return ans;
	}
}
int main() {
	setlocale(LC_ALL, "Russian");
	int a[20];
	srand(time(0));
	int max, min;
	int sum = 0;
	cout << "Введите максимальное число, применимое в массив -> "; cin >> max;
	cout << "Введите минимальное число, применимое в массив -> "; cin >> min;
	for (int i = 0; i < 20; i++) {
		a[i] = rand() % (max - min + 1) + min;
		cout << a[i] << " ";
	}
	int k1;
	cout << "\nВведите значение k1, которое будет использовно для подсчёта суммы положительных элементов, кратных этому числу -> "; cin >> k1; cout << endl;
	for (int i = 0; i < 20; i++) {
		if ((a[i] > 0) and (a[i] % k1 == 0)) {
			sum += a[i];
		}
	}
	cout << "Под пунктом а ответ является " << sum;
	cout << "\nПод пунктом б ответ является " << ex2(max, min);
}