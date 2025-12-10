#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	int s = 0;
	for (int n = 1; n <= 12; n++) {
		cout << "---------------------" << "\ns" << n << " = " << exp(n) * ((cos(2 * n) / (n + 1))) << "\n";
		s += exp(n) * ((cos(2 * n) / (n + 1)));
	}
	cout << "answer - " << s;
}