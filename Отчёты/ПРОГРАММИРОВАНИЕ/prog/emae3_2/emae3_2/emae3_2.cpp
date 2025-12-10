#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
const int n = 3;
struct Rec1 {
    long nomer;
    string name;
    int year;
    string group;
    float sred;
};
struct Rec2 {
    string name;
    int year;
    float sred;
};
void Rec(Rec1* meow) {
    for (int i = 0; i < n; i++) {
        cout << "Введите номер записи в " << i + 1 << " файле -> ";
        cin >> meow[i].nomer;
        cout << "Введите фамилию -> ";
        cin >> ws;
        getline(cin, meow[i].name);
        cout << "Введите год рождения -> ";
        cin >> meow[i].year;
        cout << "Введите группу студента -> ";
        cin >> ws;
        getline(cin, meow[i].group);
        cout << "Введите средний балл студента -> ";
        cin >> meow[i].sred;
    }
}

void Recc(const Rec1* meow, const string& group, vector<Rec2>& meow1) {
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (meow[i].group == group) {
            Rec2 temp;
            temp.name = meow[i].name;
            temp.year = meow[i].year;
            temp.sred = meow[i].sred;
            meow1.push_back(temp);
            found = true;
        }
    }

    cout << "Студенты из группы " << group << ":\n";
    for (const auto& student : meow1) {
        cout << "Фамилия: " << student.name << ", Год рождения: " << student.year << ", Средний балл: " << student.sred << endl;
    }
}

void writeToFile(const Rec1* meow, const string& filename) {
    ofstream f(filename);
    for (int i = 0; i < n; i++) {
        f << meow[i].name << " " << meow[i].nomer << " " << meow[i].group << " " << meow[i].year << " " << meow[i].sred << endl;
    }
    f.close();
}

void writeToFile_2(const vector<Rec2>& meow1, const string& filename) {
    ofstream file(filename);
    for (const auto& student : meow1) {
        file << student.name << " " << student.year << " " << student.sred << endl;
    }
    file.close();
}
int main() {
    setlocale(LC_ALL, "RU");
    string group;
    Rec1 meow[n];
    vector<Rec2> meow1;
    cout << "Введите группу, информацию студентов которой хотите узнать -> ";
    getline(cin, group);
    Rec(meow);
    Recc(meow, group, meow1);
    writeToFile(meow, "cba.txt");
    writeToFile_2(meow1, "abc.txt");
}