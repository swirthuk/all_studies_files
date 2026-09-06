#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct Task {
	string title;
	bool done = false;
};
int main() {
	setlocale(LC_ALL, "Russian");
	vector<Task> tasks;
	while (true) {
		int choice;
		cout << "1 -> Добавить цель\n2 -> Показать цель\n3 -> Пометить как выполненную\n4 -> Удалить цель\n0 -> Выйти\n"; cin >> choice;
		switch (choice)
		{
		case 1: {
			Task newtask;
			cout << "Введите название цели: ";
			cin.ignore();
			getline(cin, newtask.title);
			tasks.push_back(newtask);
			break;
		}

		case 2: {
			if (tasks.empty()) {
				cout << "Целей нет." << endl;
			}
			else {
				for (size_t i = 0; i < tasks.size(); i++) {
					cout << i + 1 << ". " << (tasks[i].done ? "Выполнена " : "Не выполнена ") << tasks[i].title << endl;
				}
			}
		}
		case 3: {
			if (tasks.empty()) {
				cout << "Целей нет.";
			}
			else {
				for (size_t i = 0; i < tasks.size(); i++) {
					cout << i + 1 << ". " << (tasks[i].done ? "Выполнена " : "Не выполнена ") << tasks[i].title << endl;
				}
				int choice_goal;
				do {
					cout << "Введите цель, которую хотите отметить -> ";
					cin >> choice_goal;
				} while (choice_goal > tasks.size() || choice_goal < 1);
				tasks[choice_goal - 1].done = true;
				cout << "Задача помечена как выполненная!" << endl;
			}
			break;
		}
		case 4: {
			if (tasks.empty()) cout << "Список пуст." << endl;
			else {
				for (size_t i = 0; i < tasks.size(); i++) {
					cout << i + 1 << ". " << (tasks[i].done ? "Выполнена " : "Не выполнена ") << tasks[i].title << endl;
				}
				int choice_goal;
				do {
					cout << "Введите номер задачи, которую вы хотите удалить -> "; cin >> choice_goal;
				} while (choice_goal > tasks.size() || choice_goal < 1);
				tasks.erase(tasks.begin() + choice_goal - 1);
				cout << "Задача успешно удалена!";
			}
			break;
		}
		case 0: {
			ofstream file1("tasks.txt");
			for (size_t i = 0; i < tasks.size(); i++) {
				file1 << (tasks[i].done ? "1" : "0") << "|" << tasks[i].title << endl;
			}
			return 0;
		}

		default:
			cout << "Не распознано, повторите ещё раз." << endl;
			break;
		}
	}
	ifstream file("tasks.txt");
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			size_t position = line.find("|");
			string doneStr = line.substr(0, position);
			string title = line.substr(position + 1);

			Task task;
			task.done = (doneStr == "1");
			task.title = title;
			tasks.push_back(task);
		}
		file.close();
	}
}