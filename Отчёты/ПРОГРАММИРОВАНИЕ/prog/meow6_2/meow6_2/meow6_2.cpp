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
int sum_proiz(const int arr[rows][cols]) {
    int proiz = 1;
    for (int i = 0; i < rows; i++) {
        int sum = 0;
        for (int j = 0; j < cols; j++) {
            sum += arr[i][j];
        }
        proiz *= sum;
    }
    return proiz;
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
    cout << "Введите максимальное число: ";
    cin >> max;
    cout << "Введите минимальное число: ";
    cin >> min;
    int arr[rows][cols];
    int maxi[rows];
    massiv(arr, min, max);
    print_mas(arr);
    cout << "Произведение сумм строк равно: " << sum_proiz(arr);
}