#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
const int rows = 5; const int cols = 7;
using namespace std;
void massiv(int arr[rows][cols], int min, int max) {
    srand(time(0));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr[i][j] = rand() % (max - min + 1) + min;
        }
    }
}
void find_max(int arr[rows][cols], int max[rows]) {
    for (int i = 0; i < rows; i++) {
        max[i] = arr[i][0];
        for (int j = 0; j < cols; j++) {
            if (arr[i][j] > max[i]) {
                max[i] = arr[i][j];
            }
        }
    }
}
void print_max(const int max[rows]) {
    setlocale(LC_ALL, "Russian");
    cout << "Максимальные значения в каждой строке: ";
    for (int i = 0; i < rows; i++) {
        cout << setw(4) << max[i];
    }
    cout << endl;
}
void print_mas(const int arr[rows][cols]) {
    cout << "Массив: " << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << setw(4) << arr[i][j];
        }
        cout << endl;
    }
}
int main() {
    setlocale(LC_ALL, "Russian");
    int max, min;
    cout << "Введите максимальное число: "; cin >> max;
    cout << "Введите минимальное число: "; cin >> min;
    int arr[rows][cols];
    int maxi[rows];
    massiv(arr, min, max); find_max(arr, maxi); print_mas(arr); print_max(maxi);
}