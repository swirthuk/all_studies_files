#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

struct Node {
    int YDK;
    string FIO;
    string name;
    int year;
    int quantity;
    Node* next;
    Node* prev;
};

void add(Node*& head, int ydk, string fio, string name, int year, int quantity, string goal) {
    Node* newnode = new Node{ ydk, fio, name, year, quantity, nullptr, nullptr };
    if (!head) {
        head = newnode;
        return;
    }

    int choice;
    cout << "Добавить перед (1) или после (0) элемента: ";
    cin >> choice;

    Node* temp = head;
    while (temp && temp->name != goal) temp = temp->next;

    if (!temp) {
        cout << "Элемент '" << goal << "' не найден!\n";
        delete newnode;
        return;
    }

    if (choice == 0) {
        newnode->next = temp->next;
        newnode->prev = temp;
        if (temp->next) temp->next->prev = newnode;
        temp->next = newnode;
    }
    else if (choice == 1) {
        newnode->next = temp;
        newnode->prev = temp->prev;
        if (temp->prev) {
            temp->prev->next = newnode;
        }
        else {
            head = newnode;
        }
        temp->prev = newnode;
    }
    else {
        cout << "Неверный выбор!\n";
        delete newnode;
    }
}

void delete_book(Node*& head, int ydk) {
    if (!head) {
        cout << "Каталог пуст!\n";
        return;
    }

    Node* temp = head;
    while (temp && temp->YDK != ydk) temp = temp->next;

    if (!temp) {
        cout << "Книга с YDK " << ydk << " не найдена.\n";
        return;
    }

    if (temp == head) {
        head = head->next;
        if (head) head->prev = nullptr;
    }
    else {
        temp->prev->next = temp->next;
        if (temp->next) temp->next->prev = temp->prev;
    }

    delete temp;
    cout << "Книга успешно удалена.\n";
}

void print_catalog(Node* head) {
    if (!head) {
        cout << setw(5) << "Каталог пуст." <<  setw(5) << endl;
        return;
    }

    cout << setw(5) <<  "КАТАЛОГ КНИГ\n";
    while (head) {
        cout << "УДК: " << head->YDK << "\n" << "Автор: " << head->FIO << "\n" << "Название: " << head->name << "\n" << "Год: " << head->year << "\n" << "Количество: " << head->quantity << "\n" << "------------------------\n";
        head = head->next;
    }
}

void find_book(Node* head, const string& name) {
    while (head) {
        if (head->name == name) {
            cout << "Книга найдена:\n" << "УДК: " << head->YDK << "\n" << "Автор: " << head->FIO << "\n" << "Год: " << head->year << "\n" << "Количество: " << head->quantity << "\n";
            return;
        }
        head = head->next;
    }
    cout << "Книга '" << name << "' не найдена.\n";
}

void clear_catalog(Node*& head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    cout << "Каталог очищен.\n";
}
void menu() {
    Node* catalog = nullptr;
    int choice;

    while (true) {
        cout << "\n===== БИБЛИОТЕЧНЫЙ КАТАЛОГ =====\n"
            << "1. Добавить книгу\n"
            << "2. Удалить книгу\n"
            << "3. Показать весь каталог\n"
            << "4. Найти книгу по названию\n"
            << "5. Очистить каталог\n"
            << "6. Выход\n"
            << "Выберите действие: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            int ydk, year, quantity;
            string fio, name, goal;
            while (true) {
                cout << "Введите УДК: ";
                if (cin >> ydk) {
                    break;
                }
                cin.clear();
                cout << "Ошибка." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore();
            cout << "Введите ФИО автора: "; getline(cin, fio);
            cout << "Введите название книги: "; getline(cin, name);
            cout << "Введите год издания: "; cin >> year;
            cout << "Введите количество: "; cin >> quantity;
            cin.ignore();
            cout << "Введите название книги, относительно которой добавлять: ";
            getline(cin, goal);

            add(catalog, ydk, fio, name, year, quantity, goal);
        }
        else if (choice == 2) {
            int ydk;
            cout << "Введите УДК книги для удаления: "; cin >> ydk;
            delete_book(catalog, ydk);
        }
        else if (choice == 3) {
            print_catalog(catalog);
        }
        else if (choice == 4) {
            string name;
            cout << "Введите название книги для поиска: ";
            getline(cin, name);
            find_book(catalog, name);
        }
        else if (choice == 5) {
            clear_catalog(catalog);
        }
        else if (choice == 6) {
            clear_catalog(catalog);
            break;
        }
        else {
            cout << "Неверный выбор!\n";
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    menu();
}