#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));
    int n, max, min, cnt, numb;
    cnt = 0;
    numb = 0;

    cout << "Enter max digit: ";
    cin >> max;
    cout << "Enter min digit: ";
    cin >> min;
    cout << "Enter n: ";
    cin >> n;
    int* c = new int[n];
    int* x = new int[n];
    for (int i = 0; i != n; i++) {
        c[i] = rand() % (max - min + 1) + min;
        cout << c[i] << " ";
    }
    cout << "\n";

    
   
    for (int i = 0; i != n; i++) {
        if (c[i] != 0) {
            x[numb] = c[i];
            numb++;
        }
    }
    for (int i = 0; i != numb; i++) {
        cout << x[i] << " ";
    }
    cout << "\n";
}
