#include <vector>
#include <iostream>
#include <ctime>
using namespace std;

void bubble(vector<int>& A, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (A[j] > A[j + 1]) {
                swap(A[j], A[j + 1]);
            }
        }
    }
}

vector<int> non_binary(vector<int> x, int target, int n) {
    for (int i = 0; i < n; i++) {
        if (x[i] == target) { return x; }
    }
    x.insert(x.begin(), target);
    return x;
}

vector<int> binary(vector<int> x, int target, int n) {
    int left = 0, right = x.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (x[mid] == target) {
            return x;
        }
        if (x[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    x.insert(x.begin(), target);
    return x;
}

int main() {
    setlocale(LC_ALL, "RU");
    int n;
    cout << "Введите количество элементов массива -> ";
    cin >> n;
    vector<int> x(n);
    int target;
    cout << "Введите число, которое хотите найти -> ";
    cin >> target;
    srand(time(0));
    for (int i = 0; i < n; i++) {
        x[i] = rand() % 11;
    }
    cout << "Исходный массив: ";
    for (int i : x) {
        cout << i << " ";
    }
    cout << endl;
    bubble(x, n);
    vector<int> result_1 = non_binary(x, target, n);
    cout << "\nПоиск небинарным методом: ";
    for (int i : result_1) {
        cout << i << " ";
    }
    cout << endl;
    vector<int> result = binary(x, target, n);
    cout << "\nПоиск бинарным методом: ";
    for (int i : result) {
        cout << i << " ";
    }
    cout << endl;
}
