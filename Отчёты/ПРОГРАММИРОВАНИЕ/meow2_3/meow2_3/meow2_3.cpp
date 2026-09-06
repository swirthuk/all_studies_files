#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	float a, b, maxi, mini, d;
	cout << "Enter any a: ";
	cin >> a;
	cout << "Enter any b: ";
	cin >> b;
	maxi = max(a, b);
	mini = min(a, b);
	d = (min(a, 3 * b) - 2 * sqrt(max(a, 3 * b))) / (pow(4, 3) + ((max(a, 3 * b)) / min(a, b)));
	cout << "The max digit is " << maxi << "\nThe min digit is " << mini << "\nd = " << d;
}