#include <iostream>
using namespace std;
int main() {
    setlocale(LC_ALL, "Russian");
    const int stroki = 5;
    const int stolbci = 7;
    int a[stroki][stolbci] = {
        {1, 2, 3, 4, 5, 6, 7},
        {2, 3, 4, 5, 6, 7, 8},
        {3, 4, 5, 6, 7, 8, 9},
        {4, 5, 6, 7, 8, 9, 10},
        {5, 6, 7, 8, 9, 10, 11}
    };
    int b[stolbci]; // одномерный массив для хранения макс. элементов столбцов
    for (int j = 0; j < stolbci; ++j) {
        b[j] = -1; // начальное значение для поиска максимума (с учетом, что все числа положительные)
        for (int i = 0; i < stroki; ++i) {
            if (a[i][j] > b[j]) {
                b[j] = a[i][j]; // обновляем максимум в столбце
            }
        }
    }
    cout << "Максимальные элементы каждого столбца:\n"; // вывод массива b
    for (int j = 0; j < stolbci; ++j) {
        cout << b[j] << " ";
    }
    cout << endl;
    return 0;
}