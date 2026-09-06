#include <iostream>
#include <math.h>
using namespace std;

int main()
{
	float x, y, z, s, a1, a2, a3;
	cout << "Enter any x, y and z: ";
	cin >> x >> y >> z;
	a1 = pow(y, pow(fabs(x), 1.0 / 3));
	a2 = pow(cos(y), 3) * (fabs(x - y) * (1 + (pow(sin(z), 2)) / sqrt(x + y)));
	a3 = exp(fabs(x - y)) + (x / 2);
	s = a1 + (a2/a3);
	cout << "x = " << x << "\ny = " << y << "\nz = " << z << "\ns = " << s;
}