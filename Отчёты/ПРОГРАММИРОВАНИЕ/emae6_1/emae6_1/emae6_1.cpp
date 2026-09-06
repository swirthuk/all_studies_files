#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;
void bubble(vector<int>& A, int& comparisons, int& assignments) {
    int n = A.size();
    comparisons = 0;
    assignments = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (A[j] < A[j + 1]) {
                swap(A[j], A[j + 1]);
                assignments += 3;
            }
        }
    }
}
void choice(vector<int>& A, int& comparisons, int& assignments) {
    int n = A.size();
    comparisons = 0;
    assignments = 0;

    for (int i = 0; i < n - 1; i++) {
        int index = i;
        for (int j = i + 1; j < n; j++) {
            comparisons++;
            if (A[j] > A[index]) {
                index = j;
                assignments++;
            }
        }
        if (index != i) {
            swap(A[i], A[index]);
            assignments += 3;
        }
    }
}
void insert(vector<int>& A, int& comparisons, int& assignments) {
    int n = A.size();
    comparisons = 0;
    assignments = 0;

    for (int i = 1; i < n; i++) {
        int temp = A[i];
        assignments++;
        int j = i - 1;

        while (j >= 0) {
            comparisons++;
            if (A[j] < temp) {
                A[j + 1] = A[j];
                assignments++;
                j--;
            }
            else {
                break;
            }
        }
        A[j + 1] = temp;
        assignments++;
    }
}

void massiv(vector<int>& A, int min, int max) {
    srand(time(0));
    for (int& num : A) {
        num = rand() % (max - min + 1) + min;
    }
}

void printArray(const vector<int>& A) {
    for (int num : A) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "RU");
    int max = 10, min = 0, n;

    cout << "Enter the lenght : ";
    cin >> n;

    vector<int> A(n);
    massiv(A, min, max);

    cout << "Исходный массив: ";
    printArray(A);

    int comparisons, assignments;
    vector<int> bubbleArr = A;
    bubble(bubbleArr, comparisons, assignments);
    cout << "\nСортировка пузырьком (по убыванию): ";
    printArray(bubbleArr);
    cout << "Сравнений: " << comparisons << ", Присваиваний: " << assignments << endl;
    vector<int> choiceArr = A;
    choice(choiceArr, comparisons, assignments);
    cout << "\nСортировка выбором (по убыванию): ";
    printArray(choiceArr);
    cout << "Сравнений: " << comparisons << ", Присваиваний: " << assignments << endl;
    vector<int> insertArr = A;
    insert(insertArr, comparisons, assignments);
    cout << "\nСортировка вставками (по убыванию): ";
    printArray(insertArr);
    cout << "Сравнений: " << comparisons << ", Присваиваний: " << assignments << endl;
}