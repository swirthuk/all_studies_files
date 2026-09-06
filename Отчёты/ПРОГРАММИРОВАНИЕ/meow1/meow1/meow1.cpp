#include <iostream>
#include <math.h>
using namespace std;

int main()
{
	float a, x, y, y1, y2, z1, z2;
	cout << "Enter any a, x and y: ";
	cin >> a >> x >> y;
	float a1, a2, a3;
	a1 = (1.0 / (2 * (1 + sqrt(a))));
	a2 = 1.0 / (2 * (1 - sqrt(a)));
	a3 = (pow(a, 2) + 2.0) / (1.0 - pow(a, 3));
	y1 = a1 + a2 + a3;
	y2 = (-1) / (pow(a,2) + a + 1.0);
	float b1, b2, b3;
	b1 = pow(cos(x), 4);
	b2 = pow(sin(y), 2);
	b3 = 1.0 / 4 * pow(sin(2 * x), 2);
	z1 = b1 + b2 + b3 - 1;
	z2 = sin(y + x) * sin(y - x);
	cout << "y1 = " << y1;
	cout << "\ny2 = " << y2;
	cout << "\nz1 = " << z1;
	cout << "\nz2 = " << z2;
}