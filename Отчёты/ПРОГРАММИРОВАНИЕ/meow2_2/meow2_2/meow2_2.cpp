#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	float a; float b; int i; int x;
	cout << "Enter any i: ";
	cin >> i;
	switch (i)
	{
	case 0:
		a = 1.25;
		b = 0.357;
		cout << "a = 1.25\nb = 0.357\ny = " << pow(((a + 3 * b - 1.254) / 2 * b), 4) - exp(0.1 * b);
		break;
	case 1:
		a = 1.2;
		b = 40.3 * pow(10, -1);
		cout << "a = 1.2\nb = 40.3*0.1\ny = " << ((a - pow(2 * b, 1.0 / 3)) / (a + b)) * (b + 4) * tan(a + b);
		break;
	case -1:
		cout << "Enter any x: ";
		cin >> x;
		if (x >= 1) {
			cout << "y = " << pow((x + 3), 3);
		}
		if (x < -2) {
			cout << "y = " << -10.5 * x;
		}
		else {
			cout << "y = " << -1 * fabs(x - 12);
			break;
		}
	default:
		cout << "Enter x in [-1;1]";
	}
}