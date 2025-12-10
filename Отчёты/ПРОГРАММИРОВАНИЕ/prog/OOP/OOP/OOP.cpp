#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
using namespace std;

class Example {
private:
	vector<int> arr;
public:
	Example() {
		srand(time(0));
		arr.push_back(rand() % 11);
		arr.push_back(rand() % 11);
		arr.push_back(rand() % 11);
		arr.push_back(rand() % 11);
		arr.push_back(rand() % 11);
	}
	string name;
	int year;
	void print(){
		cout << name << " " << year << endl;
	}
	void vectorr(vector <int> arr) {
		for (int i : arr) {
			cout << i << " ";
		}
		cout << endl;
	}
};

int main() {
	Example example;
	example.name = "Petr";
	example.year = 2006;
	cout << example.name << endl;
	Example* ptr = &example;
	ptr->name = "Evgeniy";
	cout << example.name << endl;
	cout << example.vectorr;
}