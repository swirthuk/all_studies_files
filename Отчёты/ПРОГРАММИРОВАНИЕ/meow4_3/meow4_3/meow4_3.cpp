#include <iostream>
#include <cmath>
using namespace std;

int main() {
	float b, y, x, h;
	cout << "Enter any h: ";
	cin >> h;
	cout << "Enter the coordiante's of start and finish: ";
	cin >> x >> b;
	for (x; x <= b;) {
		cout << "y = " << 14 * x * x + 1.4 << "\n";
		x += h;
	}
}