#include <iostream>
using namespace std;

int cnt(int x) {
    int cnt = 0;
    while (x > 0) {
        if (x % 10 > 0) {
            cnt++;
        }
        x /= 10;
    }
    return cnt;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int x;
    bool a = 1;
    do {
        cout << "Введите х "; cin >> x;
        if (cnt(x) == 4 && ((x % 17 == 0) || (x % 7 == 0))) {
            cout << "YES\n";
        }
        else { cout << "NO\n"; }
    } while (a == 1);
}
