#include <iostream>
using namespace std;

struct Node {
    int elem;
    Node* next;
};

void push(Node*& head, int x) {
    head = new Node{ x, head };
}

void pop(Node*& head) {
    if (!head) return;
    Node* temp = head;
    head = head->next;
    delete temp;
}

int average_ariphmetic(Node*& head) {
    float sum = 0;
    int cnt = 0;
    Node* temp = head;
    while (temp) {
        sum += temp->elem;
        cnt++;
        temp = temp->next;
    }
    return (sum / cnt);
}

void print_node(Node* head) {
    while (head) {
        cout << head->elem << " ";
        head = head->next;
    }
    cout << "\n";
}

int main() {
    Node* x = nullptr;
    push(x, 10);
    push(x, 20);
    push(x, 30);
    push(x, 40);
    push(x, 50);
    push(x, 60);
    print_node(x);
    int av_ar = average_ariphmetic(x);
    pop(x);
    push(x, av_ar);
    print_node(x);
}
