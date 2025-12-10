#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

int square_sum(const vector<int>& numbers) {
    int sm = 0;
    int sizee = size(numbers);
    for (int i = 0; i < sizee; i++) {
        sm += pow(numbers[i], 2);
    }
    cout << sm;
}

int main() {
    int a[] = [1; 3; 5; 7];
    square_sum(a);
}