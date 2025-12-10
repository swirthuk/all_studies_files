#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
const int n = 3;

struct NUMBER {
    string name;
    int number;
    string comfort;
    int people;
    int cost;
};

void structure(NUMBER* meow) {
    for (int i = 0; i < n; i++) {
        cout << "Введите название " << i + 1 << " отеля -> ";
        cin >> ws;
        getline(cin, meow[i].name);
        cout << "Введите номер " << i + 1 << " комнаты -> ";
        cin >> meow[i].number;
        cout << "Введите уровень комфорта (люкс, полулюкс, стандарт, эконом) -> ";
        cin >> meow[i].comfort;
        cout << "Введите количество человек в комнате -> ";
        cin >> meow[i].people;
        cout << "Введите стоимость проживания -> ";
        cin >> meow[i].cost;
    }
}
vector<NUMBER> hostel(NUMBER* meow) {
    vector<NUMBER> filtered;
    for (int i = 0; i < n; i++) {
        if (meow[i].name.size() >= 6 && meow[i].name.substr(meow[i].name.size() - 6) == "hostel") {
            filtered.push_back(meow[i]);
        }
    }
    sort(filtered.begin(), filtered.end(), [](const NUMBER& a, const NUMBER& b) {
        return a.comfort < b.comfort; });
    return filtered;
}
void printhostel(const vector<NUMBER>& hotels) {
    if (hotels.empty()) {
        cout << "\nНет гостиниц, оканчивающихся на 'hostel'.\n";
        return;
    }
    cout << "\nГостиницы, заканчивающиеся на 'hostel', отсортированные по комфортности:\n";
    for (const auto& h : hotels) {
        cout << "Название: " << h.name << " | Номер: " << h.number
            << " | Комфорт: " << h.comfort << " | Кол-во чел: " << h.people
            << " | Цена: " << h.cost << " руб.\n";
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    NUMBER meow[n];
    structure(meow);
    vector<NUMBER> filtered = hostel(meow);
    printhostel(filtered);
}