#include <iostream>
#include <cmath>
using namespace std;

int main() {
	float x, s, i;
	int n;
	s = 1;
	i = 1;
	cout << "Enter any x and n: ";
	cin >> x >> n;
	for (i; i == n; i++) {
		s += ((pow(x, i)) / (tgamma(i + 1)));
	}
	cout << s;
}