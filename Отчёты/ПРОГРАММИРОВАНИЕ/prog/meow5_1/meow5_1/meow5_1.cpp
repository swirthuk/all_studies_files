#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
	srand(time(0));
	int n;
	int count = 0;
	int max, min;
	cout << "enter max and min: ";
	cin >> max;
	cin >> min;
	cout << "Enter n: ";
	cin >> n;
	int* a = new int[n];
	for (int i = 1; i != n; i++) {
		a[i] = rand() % (max - min + 1) + min;
		cout << a[i] << " ";
	}
	for (int i = 1; i != n; i++) {
		if ((a[i] > 0 && a[i - 1] < 0) || (a[i] < 0 && a[i - 1] > 0)) {
			count++;
		}
	}
		
	cout << "\n" << count;
	}