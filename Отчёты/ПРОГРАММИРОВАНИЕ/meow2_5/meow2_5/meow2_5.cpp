#include <iostream>
using namespace std;

int main()
{
	bool a1, a2, a3;
	int a, b, c;
	for (a = 0; a < 2; a++) {
		for (b = 0; b < 2; b++) {
			for (c = 0; c < 2; c++) {
				a1 = !(a || !b && c);
				cout << "\na = " << a1;
				a2 = a && !(b && !c);
				cout << "\nb = " << b;
				a3 = !(!a || b && c);
				cout << "\nc = " << c;
			}
		}
	}
}