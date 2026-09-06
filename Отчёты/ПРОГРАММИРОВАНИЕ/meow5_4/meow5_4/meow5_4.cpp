#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
	int summ = 0;
	int numb = 0;
	int n, max, min;
	cout << "Enter n: ";
	cin >> n;
	cout << "Enter max: ";
	cin >> max;
	cout << "Enter min: ";
	cin >> min;
	int* a = new int[n];
	for (int i = 0; i < n; i++) {
		a[i] = rand() % (max - min + 1) + min;
		cout << a[i] << " ";
	}
	cout << "\n";
	//example: int a[6] = {1, 4, 5, 23, -1, 0};
	for (int i = 0; i < n; i++) {
		if (a[i] <= 0) {
			cout << "sum = " << summ << "\n" << "number = " << numb;
			break;
		}
		else {
			summ += a[i];
			numb++;
		}
	}
}