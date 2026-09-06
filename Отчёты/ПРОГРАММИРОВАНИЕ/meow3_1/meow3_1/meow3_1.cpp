#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	float x;
	cout << "Enter any x: ";
	cin >> x;
	if (x > 1.1) {
		cout << "y = " << log(2.4 * x) + 1.7 * exp(x);
	}
	if (x >= -2.1 && x <= 1.05) {
		cout << "y = " << - 36.2 * pow(x, 2) + cos(x);
	}
	if (x < -2.1) {
		cout << "y = " << (sqrt(fabs(x + 33))) / 2.0;
	}
}