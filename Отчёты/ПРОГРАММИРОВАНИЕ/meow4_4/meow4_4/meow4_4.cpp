#include <iostream>
#include <cmath>
using namespace std;

int main() {
	float x; int m;
	double s = 1.0;
	int n = 1;
	cout << "Enter any m: ";
	cin >> m;
	cout << "Enter any x: ";
	cin >> x;
	while (n < m) {
		s += (pow(x, n)) / tgamma(n + 1);
		n += 1;
	}
	cout << s;
}