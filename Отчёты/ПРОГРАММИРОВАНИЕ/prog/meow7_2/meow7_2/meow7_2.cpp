#include <iostream>
#include <cstring>
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	int cnt = 0;
	char a[] = "meow=meow=meowmeow==meowmeowmeow=meow=!lolololol=ow";
	for (int i = 0; i < strlen(a); i++) {
		if (a[i] == '=') { cnt++; }
	}
	cout << "Количество знаков '=' в тексте равно -> " << cnt;
}