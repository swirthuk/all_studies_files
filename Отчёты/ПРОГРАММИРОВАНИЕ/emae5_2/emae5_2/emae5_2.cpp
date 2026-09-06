#include <iostream>
#include <string>
using namespace std;

int main() {
    string a = "FJGFJG , sjfopajgogkedaegjea-okgjaogj oajgosjgeosjg osgknswgkr---n- sjkgnsrljgns";

    for (size_t i = 0; i < a.size();) {
        if ((i + 1 < a.size() && a[i + 1] == ',' && a[i] == ' ') || (a[i] == '-') || (i + 1 < a.size() && a[i + 1] == ' ' && a[i] == ' ')) {
            a.erase(i, 1);
        }
        else {
            i++;
        }
    }

    cout << a;
}
