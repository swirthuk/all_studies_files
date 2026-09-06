#include <iostream>
#include <cstring>
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	char a[] = "kl0p1k loves some0ne from 19 years old person291";
	int cnt = 0;
	int max = -100000;
	for (int i = 0; i < strlen(a); i++) {
		if (isdigit(a[i])) {
			int digit = a[i] - '0';
			cnt++;
			if (digit > max) { max = digit; }
		}
	}
	cout << "Количество цифр в тексте -> " << cnt << "\nМаксимальная цифра в числе -> " << max;
}