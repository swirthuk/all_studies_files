#include <iostream>
#include <string>
using namespace std;
class Building {
private:
	int year;
	string type;
public:
	void get_info(int x, string y) {
		year = x;
		type = y;
	}
	void print_info() {
		cout << "The type of build is " << type << ". Build's year is " << year << endl;
	}
};

int main() {
	Building house;
	house.get_info(2006, "sauna");
	house.print_info();

	return 0;
}