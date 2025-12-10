#include <cmath>
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

int main() {
	srand(time(0));
	int mini = 10000;
	int n, max, min;
	cout << "Enter n: ";
	cin >> n;
	cout << "Enter max digit: ";
	cin >> max;
	cout << "Enter min digit: ";
	cin >> min;
	int* x = new int [n];
	for (int i = 1; i != n; i++) {
		x[i] = rand() % (max - min + 1) + min;
		cout << x[i] << " ";
	}
	cout << "\n";
	for (int i = 1; i != n; i++) {
		if (x[i] < mini) {
			mini = x[i];
		}
	}
	for (int i = 1; i != n; i++) {
		x[i] = x[i] + mini;
		cout << x[i] << " ";
	}
}