#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
void massiv(int* arr, int rows, int max, int min) {
    srand(time(0));
    for (int i = 0; i < rows; i++) {
        arr[i] = rand() % (max - min + 1) + min;
    }
}
void printmassiv(const int* arr, int size) {
    cout << "Массив: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int povtors(const int* arr, int size, int povtor) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == povtor) {
            count++;
        }
    }
    return count;
}

int main() {
    setlocale(LC_ALL, "Russian");
    int n, m, max, min;
    cout << "Введите размер первого массива: ";
    cin >> n;
    cout << "Введите размер второго массива: ";
    cin >> m;
    cout << "Введите максимальное число: ";
    cin >> max;
    cout << "Введите минимальное число: ";
    cin >> min;
    int* x = new int[n];
    int* y = new int[m];
    massiv(x, n, max, min);
    massiv(y, m, max, min);
    cout << "Первый массив: ";
    printmassiv(x, n);
    cout << "Второй массив: ";
    printmassiv(y, m);
    int last = x[n - 1];
    int povtor = povtors(y, m, last);
    cout << "Последний элемент первого массива: " << last << endl;
    cout << "Количество вхождений во втором массиве: " << povtor << endl;
}
