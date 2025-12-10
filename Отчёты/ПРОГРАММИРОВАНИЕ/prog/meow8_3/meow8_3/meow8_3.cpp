#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

void massiv(int** arr, int rows, int cols, int max, int min) {
    srand(time(0));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr[i][j] = rand() % (max - min + 1) + min;
        }
    }
}

void printmassiv(int** arr, int rows, int cols) {
    cout << "Массив: " << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << setw(4) << arr[i][j];
        }
        cout << endl;
    }
}

void find_min(int** arr, int rows, int cols, int* b) {
    for (int i = 0; i < rows; i++) {
        b[i] = arr[i][0];
        for (int j = 1; j < cols; j++) {
            if (arr[i][j] < b[i]) { b[i] = arr[i][j]; }
        }
    }
}
void exercise(int** arr, int rows, int cols, int* b, int** ex) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            ex[i][j] = arr[i][j] - b[i];
        }
    }
}
void printmassivex(int** ex, int rows, int cols) {
    cout << "Результат обработки массива: " << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << setw(4) << ex[i][j];
        }
        cout << endl;
    }
}
int main() {
    setlocale(LC_ALL, "Russian");
    int rows, cols, max, min;
    cout << "Введите количество строк массива: "; cin >> rows;
    cout << "Введите количество столбцов массива: "; cin >> cols;
    cout << "Введите максимальное число: "; cin >> max;
    cout << "Введите минимальное число: "; cin >> min;
    int** a = new int* [rows];
    for (int i = 0; i < rows; i++) {
        a[i] = new int[cols];
    }
    int* b = new int[rows];
    int** ex = new int* [rows];
    for (int i = 0; i < rows; i++) {
        ex[i] = new int[cols];
    }
    massiv(a, rows, cols, max, min);
    cout << "Исходный массив:" << endl;
    printmassiv(a, rows, cols);
    find_min(a, rows, cols, b);
    exercise(a, rows, cols, b, ex);
    printmassivex(ex, rows, cols);
}
