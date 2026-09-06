#include <iostream>
#include <math.h>
using namespace std;
int main()
{
	float x, b, z, a1, a2, a3, a4;
	cout << "Enter any x: ";
	cin >> x;
	cout << "Enter any b: ";
	cin >> b;
	a1 = pow(sqrt((x + 1) / (x - 1)), 3);
	a2 = 2 * b * log(cos(pow(4 - x, 1.0 / 5)));
	a3 = 1.0/tan(b);
	a4 = (log10(pow(x, 2))) / 120;
	z = a1+a2+a3+a4;
	cout << "GRUPPA - 594-2" << "\nVARIANT - N11" << "\n------------------" << "\nx = " << x << "\nb = " << b << "\n----------------\nZ = " << z << "\n-----------------\nTancerev Andrew";
}