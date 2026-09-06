#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <vector>
using namespace std;
int n = 8;

void digits_for_matrix(ofstream& f_out, int max, int min) {
    srand(time(0));
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            f_out << rand() % (max - min + 1) + min << setw(4);
        }
        f_out << endl;
    }
}
vector<int> positive_digits_in_B(ifstream& f_in) {
    int B[8][8];
    vector<int> x(8, 0);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            f_in >> B[i][j];
        }
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (B[i][j] > 0) {
                x[i] += B[i][j];
            }
        }
    }
    return x;
}
void product(ifstream& f_in, const vector<int>& x, int n) {
    int b = 0;
    int A[8][8];
    int c[8] = { 0 };

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            f_in >> A[i][j];
        }
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            c[i] += A[i][j] * x[j];
        }
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (c[j] < c[j + 1]) {
                b = c[j]; c[j] = c[j + 1]; c[j + 1] = b;
            }
        }
    }
    cout << "Результат умножения матрицы на вектор: ";
    for (int i = 0; i < 8; i++) {
        cout << c[i] << " ";
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "RU");
    int max, min;
    cout << "Максимальное число массива -> "; cin >> max;
    cout << "Минимальное число массива -> "; cin >> min;
    ofstream f_1("abc.txt"), f_2("cba.txt");
    if (!f_1.is_open()) {
        cerr << "Ошибка открытия файла abc.txt" << endl;
        return 1;
    }
    digits_for_matrix(f_1, max, min);
    digits_for_matrix(f_2, max, min);
    f_1.close();
    f_2.close();
    ifstream f_in_1("abc.txt"), f_in_2("cba.txt");
    vector<int> x = positive_digits_in_B(f_in_2);
    product(f_in_1, x, n);
    f_in_1.close();
    f_in_2.close();
}