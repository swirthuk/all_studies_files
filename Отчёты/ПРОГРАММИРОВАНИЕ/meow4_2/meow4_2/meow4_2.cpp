#include <iostream>
#include <cmath>
using namespace std;

int main() {
	float x = 0.47;
	int l = 1;
    float raz = pow(10, -4);
	cout << "--------summa--------\n";
	double s = 0;
    double term;
    do {
        term = atan(2 * l) / (tgamma(l + 1) - x);
        s += term;
        cout << "-------- " << s << " --------\n";
        l++;
    } while (fabs(term) > raz);
}