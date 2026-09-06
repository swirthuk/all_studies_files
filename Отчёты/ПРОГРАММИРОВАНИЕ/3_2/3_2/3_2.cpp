#include <iostream>
#include <fstream>
#include <locale>
using namespace std;
const int maxSize = 3;

struct Rec1 {
    long nonner;
    char name[30];
    int year;
    float sred;
};

struct Rec2 {
    char name[20];
    int year;
    float sred;
};

int initializeStudents(Rec1* students, int maxSize) {
    for (int i = 0; i < maxSize; i++) {
        cout << "Введите фамилию " << i + 1 << " студента -> "; cin >> students[i].name;
        cout << "Введите номер " << i + 1 << " студента -> "; cin >> students[i].nonner;
        cout << "Введите год рождения " << i + 1 << " студента -> "; cin >> students[i].year;
        cout << "Введите средний балл " << i + 1 << " студента -> "; cin >> students[i].sred;
    }
    return maxSize;
}
void writeToFile(const Rec1* students, const string& filename) {
    ofstream f(filename);
    for (int i = 0; i < maxSize; i++) {
        f << students[i].name << " " << students[i].nonner << " " << students[i].year << " " << students[i].sred<< endl;
    }
    f.close();
}

int findTopStudents(const Rec1* students, int count, Rec2* topStudents, int maxSize) {
    if (count == 0) return 0;

    float maxSred = students[0].sred;
    for (int i = 1; i < count; ++i) {
        if (students[i].sred > maxSred) {
            maxSred = students[i].sred;
        }
    }

    int topCount = 0;
    for (int i = 0; i < count; ++i) {
        if (students[i].sred == maxSred && topCount < maxSize) {
            int j;
            for (j = 0; j < 19 && students[i].name[j] != '\0'; j++) {
                topStudents[topCount].name[j] = students[i].name[j];
            }
            topStudents[topCount].name[j] = '\0';
            topStudents[topCount].year = students[i].year;
            topStudents[topCount].sred = students[i].sred;
            topCount++;
        }
    }
    return topCount;
}

void printStudents(const Rec2* students, int count) {
    for (int i = 0; i < count; ++i) {
        cout << "Фамилия: " << students[i].name << ", Год рождения: " << students[i].year
            << ", Средний балл: " << students[i].sred << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    ofstream outFile("output.txt");
    if (!outFile) {
        cerr << "Ошибка: файл output.txt не может быть создан!" << endl;
        return 1;
    }

    Rec1 students[maxSize];
    Rec2 topStudents[maxSize];

    int studentCount = initializeStudents(students, maxSize);
    writeToFile(students, "input.txt");
    if (studentCount == 0) {
        cerr << "Ошибка: нет данных для обработки!" << endl;
        return 1;
    }

    int topStudentCount = findTopStudents(students, studentCount, topStudents, maxSize);

    cout << "\nСтуденты с наибольшим средним баллом:\n";
    printStudents(topStudents, topStudentCount);

    for (int i = 0; i < topStudentCount; ++i) {
        outFile << topStudents[i].name << " " << topStudents[i].year << " " << topStudents[i].sred << endl;
    }

    return 0;
}
