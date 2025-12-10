#include <iostream>
#include <cstring>

using namespace std;

int main() {
    char a[100] = "The pers0n is an amazing b0y which imaginate to have d1nner";
    char* word;
    char* context = nullptr;

    word = strtok_s(a, " ", &context);

    while (word != NULL) {
        bool hasDigit = false;
        for (int i = 0; word[i] != '\0'; i++) {
            if (isdigit(word[i])) {
                hasDigit = true;
                break;
            }
        }
        if (!hasDigit) {
            cout << word << endl;
        }
        word = strtok_s(NULL, " ", &context);
    }
}
