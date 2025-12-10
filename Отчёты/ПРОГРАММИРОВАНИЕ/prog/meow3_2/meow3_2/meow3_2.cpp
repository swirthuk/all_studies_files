#include <iostream>
#include <cmath>
using namespace std;

int main() {
	float h, y, x, a, b;
	int i = 1;
	cout << "Enter any h: ";
	cin >> h;
	cout << "Enter any a, b: ";
	cin >> a >> b;
	x = a;
	while (x <= b) {
		cout << "y" << i << " = " << 14 * pow(x, 2) + 1.4 << "\n";
		i += 1;
		x += h;
	}
}