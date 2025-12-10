#include <iostream>
#include <fstream>	
using namespace std;
int even(ifstream& f_in, int n) {
	int num, sum = 0;
	while (f_in >> num) {
		if (num % 2 == 0) { sum += num; }
	}
	return sum;
}
int main() {
	setlocale(LC_ALL, "RU");
	int n, a;
	ofstream f("abc.txt");
	cout << "Введите количество целых чисел -> "; cin >> n; cout << "\n";
	for (int i = 0; i < n; i++) {
		cout << "Введите число " << i+1 << " -> "; cin >> a;
		if (i < n - 1) {
			f << a << "\t";
		}
		else { f << a; }
	}
	f.close();
	ifstream f_in("abc.txt");
	cout << "Сумма чётных элементов -> " << even(f_in, n);
	f.close();
}