#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

bool is_simple(int n) {
    if (n < 2) return true;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

void bubble(vector<vector<int>>& A, int m, int n) {
    vector<int> temp(m);
    for (int i = 0; i < m; i++) {
        int k = 0;
        for (int j = 0; j < n; j++) {
            if (is_simple(A[i][j])) { k++; }
        }
        temp[i] = k;
    }
    for (int i = 0; i < m - 1; i++) {
        for (int j = 0; j < m - i - 1; j++) {
            if (temp[j] < temp[j + 1]) {
                swap(A[j], A[j + 1]);
                swap(temp[j], temp[j + 1]);
            }
        }
    }
}

void print_massiv(const vector<vector<int>>& A) {
    for (const auto& row : A) {
        for (int elem : row) {
            cout << elem << " ";
        }
        cout << "\n";
    }
}

int main() {
    srand(time(0));
    setlocale(LC_ALL, "Russian");
    int m = 5;
    int n = 7;
    vector<vector<int>> A(m, vector<int>(n));
    for (auto& row : A) {
        for (int& elem : row) {
            elem = rand() % 11;
        }
    }
    cout << "Исходный массив: " << "\n";
    print_massiv(A);
    bubble(A, m, n);
    cout << "\nОтсортированный массив: " << "\n";
    print_massiv(A);
}
