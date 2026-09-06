#include <iostream>
#include <cmath>
using namespace std;

int main() {
	float s = 0.0;
	int n = 1;
	while (n <= 12) {
		s += exp(n) * ((cos(2 * n)) / (n + 1));
		n += 1;
	}
	cout << s;
}