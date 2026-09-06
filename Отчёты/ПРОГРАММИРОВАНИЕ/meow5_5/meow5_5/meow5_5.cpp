#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
	srand(time(0));
	int n, max, min;
	int numb = 0;
	int maxi = -10000;
	cout << "Enter n: ";
	cin >> n;
	cout << "Enter max: ";
	cin >> max;
	cout << "Enter min: ";
	cin >> min;
	int* a = new int[n];
	for (int i = 0; i != n; i++) {
		a[i] = rand() % (max - min + 1) + min;
		cout << a[i] << " ";
	}
	cout << "\n";
	for (int i = 0; i != n; i++) {
		if (a[i] > maxi) {
			maxi = a[i];
		}
	}
	for (int i = 0; i != n; i++) {
		if (a[i] != maxi) {
			numb++;
		}
		else { break; }
	}
	int last = a[n - 1];
	a[numb] = last;
	a[n - 1] = maxi;
	for (int i = 0; i != n; i++) {
		cout << a[i] << " ";
	}
}