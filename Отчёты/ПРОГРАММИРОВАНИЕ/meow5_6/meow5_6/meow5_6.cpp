#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int main() {
    srand(time(0));
    int max, min, n, m;
    int summ = 0;
    cout << "Enter max: ";
    cin >> max;
    cout << "Enter min: ";
    cin >> min;
    cout << "Enter the numbers of lines: ";
    cin >> n;
    m = 3;
    cout << "a | stolb 0 | stolb 1 | stolb 2 |" << endl;
    int** a = new int* [n];
    for (int i = 0; i < n; i++) {
        a[i] = new int[m];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a[i][j] = rand() % (max - min + 1) + min;
            if (a[i][j] < 0) {
                summ += a[i][j];
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << "stroka " << i + 1 << " | ";
        for (int j = 0; j < m; j++) {
            cout << a[i][j] << " | ";
        }
        cout << endl;
    }
    cout << "The sum of negatives digits is " << summ;
}