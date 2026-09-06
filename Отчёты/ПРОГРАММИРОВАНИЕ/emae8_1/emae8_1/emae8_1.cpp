#include <iostream>
#include <vector>
using namespace std;
struct Node {
    int elem;
    Node* next;
};
void full_Node(Node*& head, int x) {
    Node* a = new Node{ x, head };
    head = a;
}
void print(Node* head) {
    Node* temp = head;
    while (temp) {
        cout << temp->elem << " -> ";
        temp = temp->next;
    }
    cout << "nullptr" << endl;
}
void delete_elem(Node*& head) {
    if (!head) return;

    vector<int> values;
    vector<int> counts;
    Node* temp = head;
    while (temp) {
        auto x = find(values.begin(), values.end(), temp->elem);
        if (x != values.end()) {
            counts[x - values.begin()]++;
        }
        else {
            values.push_back(temp->elem);
            counts.push_back(1);
        }
        temp = temp->next;
    }
    while (head && counts[find(values.begin(), values.end(), head->elem) - values.begin()] == 1) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    if (!head) return;
    temp = head;
    while (temp->next) {
        int index = find(values.begin(), values.end(), temp->next->elem) - values.begin();
        if (counts[index] == 1) {
            Node* toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
        }
        else {
            temp = temp->next;
        }
    }
}
int main() {
    setlocale(LC_ALL, "RU");
    Node* head = nullptr;
    full_Node(head, 20);
    full_Node(head, 30);
    full_Node(head, 10);
    full_Node(head, 20);
    full_Node(head, 40);
    full_Node(head, 10);
    full_Node(head, 50);
    print(head);
    delete_elem(head);
    print(head);
}
