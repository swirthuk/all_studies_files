#include <iostream>
#include <string>
using namespace std;

int main() {
	string lmao = "hefahgejg435355wtkwentkwj43525;rtwmgkfm++32t;knkl4gnw";
	string answer = "";
	for (int i = 0; i < lmao.size(); i++) {
		if (isalpha(lmao[i])) {
			answer += lmao[i];
		}
	}
	cout << answer;
}