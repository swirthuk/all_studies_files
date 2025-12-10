#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Node {
    string term;
    vector<string> description;
    Node* prev;
    Node* next;
};

void full_node(Node*& head, const string& term, const vector<string>& desc) {
    Node* newNode = new Node{ term, desc, nullptr, nullptr };
    if (!head) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = newNode;
    newNode->prev = temp;
}

void show_all(Node* head) {
    if (!head) {
        cout << "Список помощи пуст.\n";
        return;
    }
    Node* temp = head;
    while (temp) {
        cout << "\nТермин: " << temp->term << "\nОписание:\n";
        for (const string& line : temp->description)
            cout << "  - " << line << "\n";
        cout << "----------------------\n";
        temp = temp->next;
    }
}

void show_term(Node* head, const string& search_term) {
    Node* temp = head;
    while (temp) {
        if (temp->term == search_term) {
            cout << "\nПояснение для \"" << search_term << "\":\n";
            for (const string& line : temp->description)
                cout << "  - " << line << "\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Термин \"" << search_term << "\" не найден.\n";
}

void clear_list(Node*& head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void menu() {
    Node* head = nullptr;
    int choice;

    while (true) {
        cout << "\n===== МЕНЮ =====\n"
            << "1. Добавить термин\n"
            << "2. Показать весь текст помощи\n"
            << "3. Пояснение по термину\n"
            << "4. Выход\n"
            << "Ваш выбор: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string term;
            int lines;
            cout << "Введите термин: ";
            getline(cin, term);
            cout << "Сколько строк описания (1-5): ";
            cin >> lines;
            cin.ignore();

            if (lines < 1 || lines > 5) {
                cout << "Ошибка: допустимо от 1 до 5 строк.\n";
                continue;
            }

            vector<string> desc(lines);
            cout << "Введите описание:\n";
            for (int i = 0; i < lines; ++i) {
                cout << i + 1 << ": ";
                getline(cin, desc[i]);
            }

            full_node(head, term, desc);
        }
        else if (choice == 2) {
            show_all(head);
        }
        else if (choice == 3) {
            string search;
            cout << "Введите термин: ";
            getline(cin, search);
            show_term(head, search);
        }
        else if (choice == 4) {
            clear_list(head);
            cout << "Выход...\n";
            break;
        }
        else {
            cout << "Неверный ввод. Повторите.\n";
        }
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    menu();
    return 0;
}
