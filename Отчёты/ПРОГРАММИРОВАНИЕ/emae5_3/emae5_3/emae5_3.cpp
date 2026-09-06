#include <iostream>
#include <string>
using namespace std;
int main() {
    setlocale(LC_ALL, "Russian");
    string str1 = "a b c d e f h xy";
    string str2 = "ababcbcvbsdbsgshgsjgsjgksgdkslgds";
    for (size_t i = 0; i < str1.size(); i++) {
        if (str1[i] == ' ') continue;
        int count = 0;
        for (size_t j = 0; j < str2.size(); j++) {
            if (str2[j] == str1[i]) {
                count++;
            }
        }
        cout << "Символ '" << str1[i] << "' встречался " << count << " раз\n";
    }
    char trgt = 'a';
    int ac = 0;
    for (char i : str1) {
        if (i == trgt) {
            ac++;
        }
    }
    cout << "Количество '" << trgt << "' в первой строке -> " << ac << endl;
}
