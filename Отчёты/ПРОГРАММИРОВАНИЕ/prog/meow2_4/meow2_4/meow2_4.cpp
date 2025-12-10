#include <iostream>
#include <cmath>
using namespace std;

int main()
{	
	setlocale(LC_ALL, "Russian");
	int k, a;
	cout << "Enter any k: ";
	cin >> k;
	if (k > 1 && k < 5) {
		a = 2;
	}
	if (k >= 5) {
		a = 3;
	}
	else {
		a = k;
	}
	switch (a)
	{
	case 1:
		cout << "Мы нашли 1 гриб";
		break;
	case 2:
		cout << "Мы нашли " << k << " гриба";
		break;
	case 3:
		cout << "Мы нашли " << k << " грибов";
		break;
	default:
		cout << "Мы не нашли грибов :(";
		break;
	}
}