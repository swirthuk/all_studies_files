#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Node {
    int elem;
    Node* next;
};

void print(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->elem << " ";
        temp = temp->next;
    }
    cout << "\n";
}

void push(Node*& head, int x) {
    head = new Node{ x, head };
}

void pop(Node*& head) {
    if (!head) return;
    Node* temp = head;
    head = head->next;
    delete temp;
}

int last_elem(Node* head) {
    while (head->next != nullptr) head = head->next;
    return head->elem;
}

void replace_last(Node* head, int replace) {
    while (head->next != nullptr) head = head->next;
    head->elem = replace;
}

int main() {
    srand(time(0));
    Node* head = nullptr;
    push(head, rand() % 16 + 1);
    push(head, rand() % 16 + 1);
    push(head, rand() % 16 + 1);
    push(head, rand() % 16 + 1);
    push(head, rand() % 16 + 1);
    print(head);
    int last = last_elem(head);
    int first = head->elem;
    pop(head);
    push(head, last);
    replace_last(head, first);
    print(head);
}